# Simulation or Test Tools

## Overview

This folder contains scripts, sample packets, and test utilities used to validate the ignition telemetry software without requiring the full hardware setup.

The tools in this folder are mainly for dashboard testing, WebSocket testing, telemetry-format verification, and software debugging.

## Purpose

This folder may be used for:

* WebSocket telemetry simulators.
* Dashboard test scripts.
* Sample telemetry packet generators.
* CSV replay tools.
* Serial monitor logs.
* Offline dashboard testing.
* Communication debugging.
* Sensor data simulation.

## Recommended Folder Structure

```text
Simulation_or_Test_Tools/
├── README.md
├── WebSocket_Simulator/
├── CSV_Replay/
├── Sample_Telemetry_Packets/
└── Test_Logs/
```

## Example Use Cases

| Tool                     | Purpose                                               |
| ------------------------ | ----------------------------------------------------- |
| WebSocket simulator      | Sends fake telemetry to the dashboard for testing     |
| CSV replay script        | Replays saved test data into the dashboard            |
| Sample telemetry packets | Shows the expected JSON format from the ESP32         |
| Test logs                | Stores software test observations and debugging notes |

## Expected Telemetry Variables

| Variable       |      Unit | Description                               |
| -------------- | --------: | ----------------------------------------- |
| Temperature    |        °C | Simulated or received DS18B20 value       |
| Pressure       | kPa / bar | Simulated or received pressure value      |
| Thrust         |         N | Simulated or received load-cell value     |
| Armed State    |    Status | Simulated system arming condition         |
| Ignition State |    Status | Simulated ignition-output state           |
| Time           |    s / ms | Timestamp used for plotting and recording |

## Notes

Simulation tools are for software validation only. They do not replace full hardware testing, safety procedures, sensor calibration, or approved static-test operations.

Any simulated data must be clearly labelled so that it is not confused with real static-test data.
