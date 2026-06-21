# Required Libraries — Igniter Board Firmware

## Overview

This file lists the libraries required by the igniter board firmware.

## Libraries

| Library | Purpose |
|---|---|
| `WiFi.h` | ESP32 Wi-Fi mode setup |
| `esp_now.h` | ESP-NOW communication |
| `HX711_ADC.h` | HX711 load-cell data acquisition |
| `OneWire.h` | OneWire communication for DS18B20 |
| `DallasTemperature.h` | DS18B20 temperature reading |
| `Arduino.h` | Core Arduino functions |

## Notes

- The firmware uses the ESP32 Arduino core.
- The receive callback uses the ESP32 core 3.x callback format.
- Confirm the installed HX711 library matches `HX711_ADC.h`.
- Record tested library versions after successful compilation.
