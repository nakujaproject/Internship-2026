# Firmware Integration Notes

## Overview

This document explains how the Nakuja ignition system firmware components work together.

The system uses two ESP32 boards:

1. **Igniter Board** — reads sensor data and controls the ignition-output switching stage.
2. **Trigger Board** — receives telemetry from the igniter board, sends ignition commands, and forwards telemetry to the web dashboard.

The dashboard receives real-time telemetry from the trigger board through a WebSocket connection.

## Firmware Data Flow

```text
Igniter Board
    ↓
ESP-NOW telemetry
    ↓
Trigger Board
    ↓
Wi-Fi Access Point + WebSocket
    ↓
Web Dashboard
```

## Igniter Board Role

The igniter board is positioned near the motor or static test stand.

Main functions:

* Reads thrust from the load cell through the HX711.
* Reads temperature from the DS18B20 sensor.
* Reads pressure from the analog pressure interface.
* Receives ignition command from the trigger board using ESP-NOW.
* Controls the MOSFET-based ignition output.
* Sends telemetry to the trigger board.

## Trigger Board Role

The trigger board is positioned with the operator.

Main functions:

* Receives telemetry from the igniter board using ESP-NOW.
* Parses the received telemetry.
* Converts the telemetry into dashboard-compatible JSON.
* Creates a Wi-Fi access point named `NAKUJA`.
* Runs a WebSocket server on port `81`.
* Sends telemetry to the web dashboard.
* Sends the ignition command to the igniter board when the trigger input is activated.
* Provides local feedback through the LCD and buzzer.

## Telemetry Format from Igniter Board

The igniter board sends telemetry as a comma-separated string:

```text
thrust,temp,pressure
```

Example:

```text
12.8,27.5,101.3
```

Field order:

| Position | Field      |                  Unit | Description                     |
| -------: | ---------- | --------------------: | ------------------------------- |
|        1 | `thrust`   |                     N | Load-cell thrust value          |
|        2 | `temp`     |                    °C | DS18B20 temperature value       |
|        3 | `pressure` | kPa / configured unit | Pressure sensor/interface value |

## Telemetry Format Sent to Dashboard

The trigger board converts the received telemetry into JSON before sending it to the dashboard.

Expected JSON format:

```json
{
  "thrust": 12.8,
  "temp": 27.5,
  "pressure": 101.3,
  "ignition_armed": false
}
```

The dashboard reads:

| JSON Field       | Used For                               |
| ---------------- | -------------------------------------- |
| `thrust`         | Thrust card and thrust chart           |
| `temp`           | Temperature card and temperature chart |
| `pressure`       | Pressure card and pressure chart       |
| `ignition_armed` | Event/status display                   |
| `event`          | Optional event log message             |

## Ignition Command Format

The trigger board sends the ignition command to the igniter board through ESP-NOW.

Current command:

```text
on
```

When the igniter board receives `on`, it starts the firmware ignition window and drives the MOSFET output for the configured duration.

## Important Safety Notes

* The ESP32 must not directly power the ignition load.
* The ESP32 output pin should only control the MOSFET switching stage.
* The ignition-output window is limited in firmware.
* A proper arming condition should be added when the final hardware arm switch is confirmed.
* Firmware testing must be done only under approved Nakuja Project safety procedures.

## Current Pin Summary

### Igniter Board

| Function              | ESP32 Pin |
| --------------------- | --------: |
| MOSFET gate           |    GPIO26 |
| HX711 DOUT            |    GPIO33 |
| HX711 SCK             |    GPIO32 |
| DS18B20 data          |    GPIO14 |
| Pressure analog input |    GPIO13 |

### Trigger Board

| Function        | ESP32 Pin |
| --------------- | --------: |
| Buzzer          |    GPIO18 |
| Status button   |    GPIO32 |
| LCD I2C address |    `0x3F` |
| WebSocket port  |      `81` |

## Integration Checklist

Before testing both boards together:

* [ ] Igniter firmware compiles successfully.
* [ ] Trigger firmware compiles successfully.
* [ ] `pitches.h` exists in the trigger firmware folder.
* [ ] ESP32 board package is installed.
* [ ] Required libraries are installed.
* [ ] Igniter board boots with ignition output LOW.
* [ ] Trigger board creates the `NAKUJA` Wi-Fi access point.
* [ ] Dashboard connects to the trigger board WebSocket server.
* [ ] Igniter board sends telemetry in `thrust,temp,pressure` format.
* [ ] Trigger board converts telemetry to JSON.
* [ ] Dashboard cards update correctly.
* [ ] Dashboard charts update correctly.
* [ ] CSV recording and download are tested.
* [ ] Ignition command is tested only under approved safe conditions.

## Known Pending Improvements

| Area                         | Status                                  |
| ---------------------------- | --------------------------------------- |
| Hardware arming input        | Pending final pin confirmation          |
| Pressure calibration         | Pending final validation                |
| Load-cell calibration factor | Requires final calibration confirmation |
| Brownout mitigation          | Requires hardware validation            |
| Offline dashboard libraries  | Future improvement                      |
