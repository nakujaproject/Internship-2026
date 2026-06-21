# Igniter Board Firmware

## Overview

This folder contains the ESP32 firmware for the igniter-side board of the Nakuja Project ignition and real-time telemetry system.

The igniter board is positioned near the solid rocket motor or static test stand. It is responsible for reading sensor data, receiving ignition commands, controlling the ignition-output circuit, and transmitting telemetry to the trigger board.

## Main Responsibilities

* Read thrust data from the load cell through the HX711 module.
* Read temperature data from the DS18B20 temperature sensor.
* Read pressure data from the pressure transmitter/interface circuit.
* Receive wireless commands from the trigger board.
* Control the MOSFET-based ignition-output circuit.
* Enforce the programmed ignition safety window.
* Send telemetry data to the trigger board.

## Main Hardware Interfaces

| Function                | Device/Interface               | Notes                                           |
| ----------------------- | ------------------------------ | ----------------------------------------------- |
| Thrust measurement      | Load cell + HX711              | Used for static-test thrust data                |
| Temperature measurement | DS18B20                        | Digital temperature sensor                      |
| Pressure measurement    | Pressure transmitter/interface | Requires signal conditioning before ESP32 input |
| Ignition output         | MOSFET switching stage         | Controlled by ESP32 firmware                    |
| Wireless communication  | ESP-NOW                        | Receives command and sends telemetry            |

## Suggested Pin Mapping

| Function       | ESP32 Pin | Notes                   |
| -------------- | --------: | ----------------------- |
| MOSFET gate    |    GPIO26 | Ignition-output control |
| HX711 DOUT     |    GPIO33 | Load-cell data          |
| HX711 SCK      |    GPIO32 | Load-cell clock         |
| DS18B20 data   |    GPIO14 | Temperature sensor data |
| Pressure input |    GPIO13 | Analog pressure signal  |

## Recommended Folder Contents

```text
Igniter_Board_Firmware/
├── README.md
├── main.ino
├── config.example.h
├── pins.h
└── libraries.md
```

## Firmware Logic

The firmware should generally follow this sequence:

1. Initialize ESP32 pins, sensors, and communication.
2. Read thrust, temperature, and pressure values.
3. Send telemetry to the trigger board.
4. Wait for valid command from the trigger board.
5. Check arming and safety conditions.
6. Activate ignition output only when allowed.
7. Automatically disable ignition output after the safety window.
8. Continue sending telemetry and system-status data.

## Documentation Requirements

When firmware is uploaded, include:

* Firmware version.
* Required libraries.
* Board type used.
* Pin mapping.
* Upload instructions.
* Calibration assumptions.
* Known issues.
* Test notes.

## Safety Note

The ESP32 must not directly power the ignition load. It should only control the switching stage. The ignition output must remain disabled until all safety conditions are satisfied.
