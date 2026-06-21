# Pin Mapping — Ignition Circuit

## Overview

This file documents the ESP32 pin assignments used in the Nakuja Project ignition and real-time telemetry system.

The pin mapping should be updated whenever the firmware, PCB, or wiring changes.

## Igniter Board Pin Mapping

| Function             | ESP32 Pin | Direction    | Device / Interface             | Notes                                       |
| -------------------- | --------: | ------------ | ------------------------------ | ------------------------------------------- |
| Ignition MOSFET gate |    GPIO26 | Output       | IRFZ44N MOSFET                 | Controls ignition-output switching          |
| HX711 DOUT           |    GPIO33 | Input        | HX711 load-cell amplifier      | Load-cell data line                         |
| HX711 SCK            |    GPIO32 | Output       | HX711 load-cell amplifier      | Load-cell clock line                        |
| DS18B20 data         |    GPIO14 | Input / data | DS18B20 temperature sensor     | One-wire temperature data                   |
| Pressure input       |    GPIO13 | Analog input | Pressure transmitter/interface | Conditioned analog pressure signal          |
| 5 V supply           | 5 V / VIN | Power        | ESP32 and logic circuits       | From regulated supply                       |
| GND                  |       GND | Ground       | Common ground                  | Must be shared by logic and sensor circuits |

## Trigger Board Pin Mapping

| Function              |      ESP32 Pin | Direction | Device / Interface         | Notes                            |
| --------------------- | -------------: | --------- | -------------------------- | -------------------------------- |
| Buzzer                |         GPIO18 | Output    | Active buzzer              | Audio feedback                   |
| Status button         |         GPIO32 | Input     | Push button / status input | Operator input or status control |
| Wi-Fi access point    | Internal radio | Wireless  | Dashboard connection       | Local dashboard link             |
| ESP-NOW communication | Internal radio | Wireless  | Igniter board              | Board-to-board communication     |
| WebSocket server      | Internal Wi-Fi | Wireless  | Dashboard                  | Telemetry streaming              |
| 5 V supply            |      5 V / VIN | Power     | ESP32 and logic circuits   | From regulated supply            |
| GND                   |            GND | Ground    | Common ground              | Required for stable operation    |

## Communication Details

| Link                           | Method             | Notes                                |
| ------------------------------ | ------------------ | ------------------------------------ |
| Igniter board to trigger board | ESP-NOW            | Sends telemetry and receives command |
| Trigger board to dashboard     | Wi-Fi access point | Local dashboard connection           |
| Dashboard telemetry            | WebSocket, port 81 | Real-time data streaming             |

## Important Hardware Notes

* GPIO26 controls the ignition-output switching stage through the MOSFET.
* The ESP32 must not directly power the ignition load.
* The pressure transmitter/interface must be conditioned before connection to the ESP32 ADC.
* All sensor and logic grounds must share a correct reference.
* Final pin mapping must match both the firmware and PCB layout.
* Any pin change must be updated in this file, the firmware, and the wiring diagram.

## Revision History

| Date       | Revision | Change                            | Updated By       |
| ---------- | -------- | --------------------------------- | ---------------- |
| YYYY-MM-DD | Rev A    | Initial pin mapping documentation | Joel Litu Ehenzo |
