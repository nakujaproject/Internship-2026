# Telemetry Format — Web Dashboard

## Overview

This document defines the telemetry data format expected by the Nakuja ignition system web dashboard.

The dashboard receives telemetry from the trigger board through a WebSocket connection. The trigger board receives telemetry from the igniter board and forwards it to the dashboard.

## Expected WebSocket Address

```text
ws://<ESP32_IP_ADDRESS>:81
```

Example:

```text
ws://192.168.4.1:81
```

## Expected JSON Packet

```json
{
  "temp": 27.5,
  "pressure": 101.3,
  "thrust": 12.8,
  "ignition_armed": false,
  "event": "Telemetry update"
}
```

## Field Description

| Field            | Type    | Unit | Description                                                 |
| ---------------- | ------- | ---: | ----------------------------------------------------------- |
| `temp`           | Number  |   °C | Temperature reading from the DS18B20 sensor                 |
| `pressure`       | Number  |  kPa | Pressure reading from the pressure transmitter/interface    |
| `thrust`         | Number  |    N | Thrust reading from the load cell and HX711                 |
| `ignition_armed` | Boolean |    - | Shows whether the ignition system is armed                  |
| `event`          | String  |    - | Optional event message displayed in the dashboard event log |

## CSV Export Format

The dashboard records telemetry in the following format:

```csv
Stopwatch Time (HH:mm:ss.ms),Temperature (°C),Pressure (kPa),Thrust (N)
```

Example:

```csv
00:00:00.000,27.50,0.00,0.00
00:00:00.250,27.60,0.50,0.20
00:00:00.500,27.70,1.20,0.50
```

## Notes

* The dashboard expects valid JSON packets.
* Invalid or missing numerical values may be ignored.
* The WebSocket server is expected to run on port `81`.
* The trigger board should send telemetry at a stable rate suitable for dashboard plotting.
* Simulated telemetry must be clearly labelled so it is not confused with real static-test data.
