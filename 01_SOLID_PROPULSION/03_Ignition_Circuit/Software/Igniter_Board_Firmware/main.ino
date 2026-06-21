/*
  Nakuja Project — Igniter Board Firmware

  Purpose:
  - Read thrust data from HX711 load-cell module.
  - Read temperature data from DS18B20 sensor.
  - Read pressure data from analog pressure interface.
  - Receive ignition command from trigger board through ESP-NOW.
  - Control MOSFET-based ignition output.
  - Send telemetry to the trigger board.

  Notes:
  - The ESP32 does not directly power the ignition load.
  - GPIO26 only controls the MOSFET switching stage.
  - The ignition output is limited to a 15-second firmware window.
  - Telemetry format sent by this board: thrust,temp,pressure
*/

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <HX711_ADC.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// -----------------------------------------------------------------------------
// Pin Definitions
// -----------------------------------------------------------------------------

#define PRESSURE_PIN 13
#define ONE_WIRE_BUS 14
#define IGNITION_PIN 26

const int HX711_DOUT_PIN = 33;
const int HX711_SCK_PIN  = 32;

// -----------------------------------------------------------------------------
// Temperature Sensor
// -----------------------------------------------------------------------------

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

unsigned long lastTempRequest = 0;
float currentTemp = 0.0;

// -----------------------------------------------------------------------------
// Load Cell
// -----------------------------------------------------------------------------

HX711_ADC LoadCell(HX711_DOUT_PIN, HX711_SCK_PIN);

// Adjust after calibration.
const float LOAD_CELL_CALIBRATION_FACTOR = 1000.0;

// -----------------------------------------------------------------------------
// Ignition State
// -----------------------------------------------------------------------------

bool ignitionActive = false;
unsigned long ignitionStartTime = 0;

const unsigned long IGNITION_WINDOW_MS = 15000;

// -----------------------------------------------------------------------------
// Pressure Sensor Configuration
// -----------------------------------------------------------------------------

const int ADC_RESOLUTION = 4095;
const float ESP32_ADC_REFERENCE_VOLTAGE = 3.3;

// Sensor/interface calibration values.
// Ensure the analog voltage connected to the ESP32 ADC does not exceed 3.3 V.
const float SENSOR_MIN_VOLTAGE = 0.5;
const float SENSOR_MAX_VOLTAGE = 4.5;
const float SENSOR_MAX_PRESSURE = 1.2;

const int NUM_PRESSURE_READINGS = 10;

float pressureValue = 0.0;

// -----------------------------------------------------------------------------
// Function Prototypes
// -----------------------------------------------------------------------------

void receiveCallback(const esp_now_recv_info_t *recvInfo, const uint8_t *data, int dataLen);
void broadcastTelemetry(const String &message);
float mapPressure(float voltage);

// -----------------------------------------------------------------------------
// ESP-NOW Receive Callback
// -----------------------------------------------------------------------------

void receiveCallback(const esp_now_recv_info_t *recvInfo, const uint8_t *data, int dataLen) {
  char buffer[ESP_NOW_MAX_DATA_LEN + 1];

  int msgLen = min(ESP_NOW_MAX_DATA_LEN, dataLen);
  strncpy(buffer, (const char *)data, msgLen);
  buffer[msgLen] = '\0';

  if (strcmp(buffer, "on") == 0) {
    Serial.println(">>> IGNITION COMMAND RECEIVED <<<");

    ignitionActive = true;
    ignitionStartTime = millis();
  }
}

// -----------------------------------------------------------------------------
// ESP-NOW Broadcast
// -----------------------------------------------------------------------------

void broadcastTelemetry(const String &message) {
  uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);

  if (!esp_now_is_peer_exist(broadcastAddress)) {
    esp_now_add_peer(&peerInfo);
  }

  esp_now_send(broadcastAddress, (const uint8_t *)message.c_str(), message.length());
}

// -----------------------------------------------------------------------------
// Sensor Helper Functions
// -----------------------------------------------------------------------------

float mapPressure(float voltage) {
  voltage = constrain(voltage, SENSOR_MIN_VOLTAGE, SENSOR_MAX_VOLTAGE);

  return (voltage - SENSOR_MIN_VOLTAGE) *
         SENSOR_MAX_PRESSURE /
         (SENSOR_MAX_VOLTAGE - SENSOR_MIN_VOLTAGE);
}

// -----------------------------------------------------------------------------
// Setup
// -----------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);

  pinMode(PRESSURE_PIN, INPUT);
  pinMode(IGNITION_PIN, OUTPUT);

  // Safety on boot: ignition output must remain OFF.
  digitalWrite(IGNITION_PIN, LOW);

  // Configure ESP32 ADC range.
  analogSetAttenuation(ADC_11db);

  // ---------------------------------------------------------------------------
  // Temperature Sensor Setup
  // ---------------------------------------------------------------------------

  sensors.begin();
  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();

  Serial.println("DS18B20 initialized in asynchronous mode.");

  // ---------------------------------------------------------------------------
  // Load Cell Setup
  // ---------------------------------------------------------------------------

  Serial.println("Initializing HX711 load-cell interface...");

  LoadCell.begin();

  // 8 samples at 80 SPS gives approximately 100 ms smoothing.
  LoadCell.setSamplesInUse(8);

  // Startup tare.
  LoadCell.start(2000, true);

  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("HX711 timeout. Check wiring, solder bridge, and sampling-rate configuration.");
    while (1);
  }

  LoadCell.setCalFactor(LOAD_CELL_CALIBRATION_FACTOR);

  Serial.println("Load cell zeroed and ready.");

  // ---------------------------------------------------------------------------
  // ESP-NOW Setup
  // ---------------------------------------------------------------------------

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() == ESP_OK) {
    Serial.println("ESP-NOW initialization successful.");
    esp_now_register_recv_cb(receiveCallback);
  } else {
    Serial.println("ESP-NOW initialization failed. Restarting...");
    ESP.restart();
  }
}

// -----------------------------------------------------------------------------
// Main Loop
// -----------------------------------------------------------------------------

void loop() {
  // ---------------------------------------------------------------------------
  // 1. Load Cell Update
  // ---------------------------------------------------------------------------

  bool newDataAvailable = LoadCell.update();

  // ---------------------------------------------------------------------------
  // 2. Asynchronous Temperature Reading
  // ---------------------------------------------------------------------------

  if (millis() - lastTempRequest >= 1000) {
    currentTemp = sensors.getTempCByIndex(0);
    sensors.requestTemperatures();
    lastTempRequest = millis();
  }

  // ---------------------------------------------------------------------------
  // 3. Telemetry Dispatch
  // ---------------------------------------------------------------------------

  if (newDataAvailable) {
    float thrustNewtons = LoadCell.getData();

    int totalAdc = 0;

    for (int i = 0; i < NUM_PRESSURE_READINGS; i++) {
      totalAdc += analogRead(PRESSURE_PIN);
    }

    float averageVoltage =
      ((totalAdc / (float)NUM_PRESSURE_READINGS) / ADC_RESOLUTION) *
      ESP32_ADC_REFERENCE_VOLTAGE;

    pressureValue = mapPressure(averageVoltage);

    // Telemetry format: thrust,temp,pressure
    // The trigger board should parse this and forward dashboard-compatible JSON.
    String telemetry =
      String(thrustNewtons) + "," +
      String(currentTemp) + "," +
      String(pressureValue);

    broadcastTelemetry(telemetry);
  }

  // ---------------------------------------------------------------------------
  // 4. Ignition Sequencer
  // ---------------------------------------------------------------------------

  if (ignitionActive && (millis() - ignitionStartTime < IGNITION_WINDOW_MS)) {
    digitalWrite(IGNITION_PIN, HIGH);
  } else {
    digitalWrite(IGNITION_PIN, LOW);
    ignitionActive = false;
  }

  // ---------------------------------------------------------------------------
  // 5. Serial Maintenance Commands
  // ---------------------------------------------------------------------------

  if (Serial.available()) {
    char command = Serial.read();

    if (command == 't') {
      LoadCell.tareNoDelay();
      Serial.println("Tare re-initiated.");
    }
  }

  if (LoadCell.getTareStatus()) {
    Serial.println("Tare complete.");
  }
}
