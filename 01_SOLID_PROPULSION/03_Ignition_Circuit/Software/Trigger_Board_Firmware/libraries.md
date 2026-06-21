# Required Libraries — Trigger Board Firmware

## Overview

This file lists the libraries required by the trigger board firmware.

## Libraries

| Library | Purpose |
|---|---|
| `WiFi.h` | Wi-Fi access point and ESP32 wireless setup |
| `esp_now.h` | ESP-NOW communication with the igniter board |
| `WebSocketsServer.h` | WebSocket server for dashboard telemetry |
| `ArduinoJson.h` | JSON formatting for dashboard packets |
| `LiquidCrystal_I2C.h` | 16x2 I2C LCD display support |
| `Arduino.h` | Core Arduino functions |
| `pitches.h` | Local note-frequency definitions for buzzer melody |

## Notes

- The firmware uses the ESP32 Arduino core.
- The receive callback uses the ESP32 core 3.x callback format.
- The send callback uses the ESP32 core 3.x `wifi_tx_info_t` format.
- Confirm the installed WebSockets library matches `WebSocketsServer.h`.
- Confirm the installed LCD library supports the `LiquidCrystal_I2C` class.
- Record tested library versions after successful compilation.
