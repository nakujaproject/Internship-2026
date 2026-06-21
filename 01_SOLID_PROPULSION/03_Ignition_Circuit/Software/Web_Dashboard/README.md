# Web Dashboard

## Overview

This folder contains the browser-based dashboard for the Nakuja Project ignition and real-time telemetry system.

The dashboard is used to monitor thrust, pressure, temperature, connection status, arming state, and ignition events during dry runs and static motor tests. It receives telemetry through a WebSocket connection and allows recorded data to be exported as CSV files.

## Main Functions

* Display real-time thrust readings.
* Display real-time pressure readings.
* Display real-time temperature readings.
* Plot telemetry values against time.
* Show connection status.
* Log important events.
* Start and stop data recording.
* Export recorded telemetry as CSV files.
* Support review of static-test and dry-run data.

## Recommended Folder Contents

```text
Web_Dashboard/
├── README.md
├── index.html
├── style.css
├── script.js
├── assets/
├── screenshots/
└── sample_data/
```

## Main Files

| File/Folder    | Purpose                                                       |
| -------------- | ------------------------------------------------------------- |
| `index.html`   | Main dashboard page structure                                 |
| `style.css`    | Dashboard styling and layout                                  |
| `script.js`    | WebSocket connection, charting, event logging, and CSV export |
| `assets/`      | Logos, icons, and visual resources                            |
| `screenshots/` | Dashboard preview images                                      |
| `sample_data/` | Example telemetry data for testing                            |

## Dashboard Data

| Variable       |      Unit | Description                            |
| -------------- | --------: | -------------------------------------- |
| Thrust         |         N | Load-cell measurement                  |
| Pressure       | kPa / bar | Pressure transmitter/interface reading |
| Temperature    |        °C | DS18B20 reading                        |
| Armed State    |    Status | System arming condition                |
| Ignition State |    Status | Ignition-output condition              |
| Time           |    s / ms | Used for plotting and recording        |

## Communication

The dashboard receives data from the trigger board through a WebSocket connection.

```text
Trigger Board
     ↓
Wi-Fi Access Point
     ↓
WebSocket
     ↓
Browser Dashboard
```

## Development Notes

When updating the dashboard, document:

* Dashboard version.
* WebSocket IP address or hostname.
* WebSocket port.
* Telemetry packet format.
* Chart update rate.
* CSV export format.
* Known bugs.
* Screenshots of the interface.

## Testing Notes

The dashboard can be tested using:

* Live data from the trigger board.
* Simulated telemetry from Node.js or another test script.
* Sample CSV files.
* Manually generated telemetry packets.

## Safety Note

The dashboard is a monitoring and recording interface. It should not be treated as the only safety control. Physical procedures, firmware safety logic, and approved test checklists must still be followed.
