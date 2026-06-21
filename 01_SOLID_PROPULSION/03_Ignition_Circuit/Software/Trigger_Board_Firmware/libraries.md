# Required Libraries — Trigger Board Firmware

## Overview

This file lists the main libraries required by the trigger board firmware.

## Arduino / ESP32 Libraries

| Library | Purpose |
|---|---|
| WiFi | Wi-Fi access point creation |
| esp_now | ESP-NOW communication with igniter board |
| WebSocketsServer | WebSocket telemetry server |
| ArduinoJson | JSON telemetry formatting, if used |
| LiquidCrystal_I2C | LCD display support, if used |

## Notes

- Confirm exact library names used in the final firmware.
- Record tested library versions where possible.
- Update this file whenever a dependency changes.
