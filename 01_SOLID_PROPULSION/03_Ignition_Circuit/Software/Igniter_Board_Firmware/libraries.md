# Required Libraries — Igniter Board Firmware

## Overview

This file lists the main libraries required by the igniter board firmware.

## Arduino / ESP32 Libraries

| Library | Purpose |
|---|---|
| WiFi | ESP32 wireless support |
| esp_now | ESP-NOW communication |
| HX711 / HX711_ADC | Load-cell data acquisition |
| OneWire | DS18B20 communication |
| DallasTemperature | Temperature reading |
| ArduinoJson | Telemetry packet formatting, if used |

## Notes

- Confirm the exact library names used in the final firmware.
- Record tested library versions where possible.
- Update this file whenever a new dependency is added.
- If Arduino IDE is used, note the board package version.
- If PlatformIO is used, document dependencies in `platformio.ini`.
