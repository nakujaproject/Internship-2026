/*
  Nakuja Project — Trigger Board Firmware

  Purpose:
  - Receive telemetry from the igniter board through ESP-NOW.
  - Parse igniter telemetry in CSV format: thrust,temp,pressure.
  - Convert telemetry into JSON for the web dashboard.
  - Create a Wi-Fi access point for dashboard connection.
  - Run a WebSocket server on port 81.
  - Send ignition command to the igniter board when the operator button is released.
  - Provide local feedback through LCD and buzzer.

  Dashboard JSON format:
  {
    "thrust": 12.8,
    "temp": 27.5,
    "pressure": 101.3,
    "ignition_armed": false,
    "event": "Telemetry update"
  }
*/

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"

// -----------------------------------------------------------------------------
// LCD Setup
// -----------------------------------------------------------------------------

const int LCD_COLUMNS = 16;
const int LCD_ROWS = 2;

LiquidCrystal_I2C lcd(0x3F, LCD_COLUMNS, LCD_ROWS);

// -----------------------------------------------------------------------------
// Pin Definitions
// -----------------------------------------------------------------------------

#define BUZZER_PIN 18
#define STATUS_BUTTON_PIN 32

// -----------------------------------------------------------------------------
// Button State
// -----------------------------------------------------------------------------

// INPUT_PULLUP logic:
// HIGH = button released
// LOW  = button pressed
bool buttonReleased = true;

// -----------------------------------------------------------------------------
// Melody Setup
// -----------------------------------------------------------------------------

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3,
  NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4,
  4, 4, 4, 4
};

const int MELODY_LENGTH = 8;

bool isPlayingMelody = false;
int currentNote = 0;
unsigned long noteStartTime = 0;

// -----------------------------------------------------------------------------
// Wi-Fi and WebSocket Setup
// -----------------------------------------------------------------------------

const char *WIFI_AP_SSID = "NAKUJA";
const char *WIFI_AP_PASSWORD = "12345678";

const uint16_t WEBSOCKET_PORT = 81;

WebSocketsServer webSocket = WebSocketsServer(WEBSOCKET_PORT);

// -----------------------------------------------------------------------------
// Telemetry Data
// -----------------------------------------------------------------------------

float thrustVal = 0.0;
float tempVal = 0.0;
float pressureVal = 0.0;

// ESP-NOW receive buffer.
// The callback copies received data here, then loop() processes it.
volatile bool newDataReady = false;
char packetBuffer[ESP_NOW_MAX_DATA_LEN + 1];

// -----------------------------------------------------------------------------
// Timing Variables
// -----------------------------------------------------------------------------

unsigned long lastLcdUpdate = 0;
const unsigned long LCD_UPDATE_INTERVAL_MS = 250;

// -----------------------------------------------------------------------------
// Function Prototypes
// -----------------------------------------------------------------------------

void receiveCallback(const esp_now_recv_info_t *recvInfo, const uint8_t *data, int dataLen);
void sentCallback(const wifi_tx_info_t *info, esp_now_send_status_t status);
void broadcastCommand(const String &message);
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);
void updateLcdTelemetry();
void startIgnitionFeedback();
void updateMelody();

// -----------------------------------------------------------------------------
// ESP-NOW Receive Callback
// -----------------------------------------------------------------------------

void receiveCallback(const esp_now_recv_info_t *recvInfo, const uint8_t *data, int dataLen) {
  int msgLen = min(ESP_NOW_MAX_DATA_LEN, dataLen);

  strncpy(packetBuffer, (const char *)data, msgLen);
  packetBuffer[msgLen] = '\0';

  newDataReady = true;
}

// -----------------------------------------------------------------------------
// ESP-NOW Send Callback
// -----------------------------------------------------------------------------

void sentCallback(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  // Kept silent to reduce serial overhead during high-rate telemetry.
}

// -----------------------------------------------------------------------------
// ESP-NOW Broadcast Command
// -----------------------------------------------------------------------------

void broadcastCommand(const String &message) {
  uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);

  if (!esp_now_is_peer_exist(broadcastAddress)) {
    esp_now_add_peer(&peerInfo);
  }

  esp_now_send(broadcastAddress, (const uint8_t *)message.c_str(), message.length());
}

// -----------------------------------------------------------------------------
// WebSocket Event Handler
// -----------------------------------------------------------------------------

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  if (type == WStype_CONNECTED) {
    webSocket.sendTXT(num, "{\"status\":\"Connected to Trigger Board\"}");
  }
}

// -----------------------------------------------------------------------------
// Setup
// -----------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);

  pinMode(STATUS_BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  // ---------------------------------------------------------------------------
  // LCD Startup Message
  // ---------------------------------------------------------------------------

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("NAKUJA PROJECT");
  delay(1500);

  lcd.clear();
  lcd.print("SOLID PROPULSION");
  delay(1500);

  lcd.clear();

  // ---------------------------------------------------------------------------
  // Wi-Fi Access Point Setup
  // ---------------------------------------------------------------------------

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASSWORD);

  IPAddress myIP = WiFi.softAPIP();

  Serial.print("Wi-Fi AP started. IP: ");
  Serial.println(myIP);

  lcd.setCursor(0, 0);
  lcd.print("AP: NAKUJA");
  lcd.setCursor(0, 1);
  lcd.print(myIP);
  delay(2000);
  lcd.clear();

  // ---------------------------------------------------------------------------
  // ESP-NOW Setup
  // ---------------------------------------------------------------------------

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed. Restarting...");
    ESP.restart();
  }

  esp_now_register_recv_cb(receiveCallback);
  esp_now_register_send_cb(sentCallback);

  // ---------------------------------------------------------------------------
  // WebSocket Setup
  // ---------------------------------------------------------------------------

  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);

  Serial.println("Trigger Board ready.");
}

// -----------------------------------------------------------------------------
// Main Loop
// -----------------------------------------------------------------------------

void loop() {
  webSocket.loop();

  // ---------------------------------------------------------------------------
  // 1. Process Telemetry from Igniter Board
  // ---------------------------------------------------------------------------

  if (newDataReady) {
    newDataReady = false;

    String dataString = String(packetBuffer);

    int firstComma = dataString.indexOf(',');
    int secondComma = dataString.indexOf(',', firstComma + 1);

    if (firstComma != -1 && secondComma != -1) {
      // Igniter telemetry format: thrust,temp,pressure
      thrustVal = dataString.substring(0, firstComma).toFloat();
      tempVal = dataString.substring(firstComma + 1, secondComma).toFloat();
      pressureVal = dataString.substring(secondComma + 1).toFloat();

      StaticJsonDocument<200> doc;

      doc["thrust"] = thrustVal;
      doc["temp"] = tempVal;
      doc["pressure"] = pressureVal;
      doc["ignition_armed"] = false;

      String jsonData;
      serializeJson(doc, jsonData);

      webSocket.broadcastTXT(jsonData);
    }
  }

  // ---------------------------------------------------------------------------
  // 2. LCD Telemetry Update
  // ---------------------------------------------------------------------------

  if (!isPlayingMelody && (millis() - lastLcdUpdate > LCD_UPDATE_INTERVAL_MS)) {
    updateLcdTelemetry();
    lastLcdUpdate = millis();
  }

  // ---------------------------------------------------------------------------
  // 3. Button Logic — Send Ignition Command on Release
  // ---------------------------------------------------------------------------

  if (digitalRead(STATUS_BUTTON_PIN) == HIGH) {
    // Button is released.
    if (!buttonReleased) {
      buttonReleased = true;

      broadcastCommand("on");

      Serial.println("Ignition command sent.");

      StaticJsonDocument<120> eventDoc;
      eventDoc["event"] = "Ignition command sent from trigger board";
      eventDoc["ignition_armed"] = true;

      String eventJson;
      serializeJson(eventDoc, eventJson);
      webSocket.broadcastTXT(eventJson);

      startIgnitionFeedback();
    }
  } else {
    // Button is pressed.
    buttonReleased = false;
  }

  // ---------------------------------------------------------------------------
  // 4. Non-Blocking Melody Player
  // ---------------------------------------------------------------------------

  updateMelody();
}

// -----------------------------------------------------------------------------
// LCD Helper
// -----------------------------------------------------------------------------

void updateLcdTelemetry() {
  lcd.setCursor(0, 0);
  lcd.print("F:");
  lcd.print(thrustVal, 1);
  lcd.print(" N    ");

  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(tempVal, 1);

  lcd.setCursor(8, 1);
  lcd.print("P:");
  lcd.print(pressureVal, 1);
  lcd.print("  ");
}

// -----------------------------------------------------------------------------
// Ignition Feedback Helper
// -----------------------------------------------------------------------------

void startIgnitionFeedback() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("! IGNITION !");
  lcd.setCursor(0, 1);
  lcd.print("CMD SENT");

  isPlayingMelody = true;
  currentNote = 0;

  int duration = 1000 / noteDurations[currentNote];
  tone(BUZZER_PIN, melody[currentNote], duration);

  noteStartTime = millis();
}

// -----------------------------------------------------------------------------
// Melody Helper
// -----------------------------------------------------------------------------

void updateMelody() {
  if (!isPlayingMelody) {
    return;
  }

  int noteDuration = 1000 / noteDurations[currentNote];
  unsigned long pauseBetweenNotes = noteDuration * 1.3;

  if (millis() - noteStartTime >= pauseBetweenNotes) {
    currentNote++;

    if (currentNote >= MELODY_LENGTH) {
      isPlayingMelody = false;
      noTone(BUZZER_PIN);
    } else {
      int nextDuration = 1000 / noteDurations[currentNote];
      tone(BUZZER_PIN, melody[currentNote], nextDuration);
      noteStartTime = millis();
    }
  }
}
