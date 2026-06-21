# Sample Dashboard Data

## Overview

This folder contains sample telemetry data for testing and documenting the Nakuja ignition web dashboard.

The files in this folder are not real static-test results. They are only used to confirm dashboard formatting, CSV export, telemetry parsing, and documentation examples.

## Recommended Files

| File | Purpose |
|---|---|
| `sample_telemetry_packet.json` | Example WebSocket telemetry packet |
| `sample_dashboard_data.csv` | Example dashboard CSV export |
| `sample_event_log.txt` | Example event log output, if required |

## Sample Data Rules

- Clearly label all sample files.
- Do not mix sample data with real test data.
- Do not use sample data for engineering conclusions.
- Real dry-run and static-test data should be stored in a separate test-data folder.
- Update the sample files when the dashboard telemetry format changes.

## Expected Telemetry Variables

| Variable | Unit | Description |
|---|---:|---|
| Temperature | °C | DS18B20 temperature reading |
| Pressure | kPa / bar | Pressure transmitter/interface reading |
| Thrust | N | Load-cell and HX711 thrust reading |
| Armed State | Status | Ignition arming condition |
| Event | Text | Optional event log message |

## Notes

Sample data is useful for software testing, documentation, and demonstrating dashboard behavior without connecting the full ignition hardware.
