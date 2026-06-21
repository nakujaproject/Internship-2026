# Software — Ignition Circuit

## Overview

This folder contains all software files for the Nakuja Project ignition and real-time telemetry system. It includes ESP32 firmware for the igniter and trigger boards, web dashboard source files, and simulation or testing tools used during development.

The software system supports wireless command transmission, real-time telemetry streaming, dashboard visualization, event logging, and CSV data export.

## Recommended Folder Structure

```text
Software/
├── README.md
├── Igniter_Board_Firmware/
├── Trigger_Board_Firmware/
├── Web_Dashboard/
└── Simulation_or_Test_Tools/
```

## Software Modules

| Module                      | Purpose                                                      |
| --------------------------- | ------------------------------------------------------------ |
| `Igniter_Board_Firmware/`   | Firmware for the test-stand-side ESP32 board                 |
| `Trigger_Board_Firmware/`   | Firmware for the operator-side ESP32 board                   |
| `Web_Dashboard/`            | Browser-based telemetry dashboard files                      |
| `Simulation_or_Test_Tools/` | Scripts or tools for testing telemetry without full hardware |

## Igniter Board Firmware

The igniter board firmware runs on the ESP32 located near the static test stand.

Main responsibilities:

* Read thrust data from the HX711 load-cell subsystem.
* Read temperature data from the DS18B20 sensor.
* Read pressure data from the pressure transmitter interface.
* Receive ignition commands from the trigger board through ESP-NOW.
* Control the MOSFET-based ignition output.
* Enforce the programmed ignition safety window.
* Send telemetry packets to the trigger board.

Recommended files:

```text
Igniter_Board_Firmware/
├── README.md
├── main.ino
├── config.example.h
├── pins.h
└── libraries.md
```

## Trigger Board Firmware

The trigger board firmware runs on the ESP32 located with the operator.

Main responsibilities:

* Receive telemetry from the igniter board.
* Send operator ignition commands to the igniter board.
* Create the local Wi-Fi access point.
* Run the WebSocket server for dashboard communication.
* Forward telemetry data to the dashboard.
* Provide operator feedback using indicators such as buzzer, LED, or display output.

Recommended files:

```text
Trigger_Board_Firmware/
├── README.md
├── main.ino
├── config.example.h
├── pins.h
└── libraries.md
```

## Web Dashboard

The web dashboard is used to monitor the static test in real time from a laptop or tablet.

Main functions:

* Display thrust, pressure, and temperature.
* Plot telemetry values against time.
* Show system connection status.
* Log important events.
* Start and stop data recording.
* Export recorded telemetry as CSV files.

Recommended files:

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

## Communication Flow

```text
Igniter Board Firmware
        ↓
ESP-NOW telemetry
        ↓
Trigger Board Firmware
        ↓
Wi-Fi Access Point + WebSocket
        ↓
Web Dashboard
        ↓
CSV Export
```

## Main Technologies

| Technology         | Use                                                  |
| ------------------ | ---------------------------------------------------- |
| ESP32              | Main microcontroller platform                        |
| ESP-NOW            | Board-to-board wireless communication                |
| Wi-Fi Access Point | Local dashboard connection                           |
| WebSocket          | Real-time telemetry streaming                        |
| HTML               | Dashboard structure                                  |
| CSS                | Dashboard styling                                    |
| JavaScript         | Dashboard logic, plotting, recording, and CSV export |
| Node.js            | Optional testing or telemetry simulation             |

## Telemetry Data

The software should handle the following main telemetry values:

| Variable       |      Unit | Description                               |
| -------------- | --------: | ----------------------------------------- |
| Thrust         |         N | Load-cell measurement through HX711       |
| Pressure       |       bar | Pressure transmitter/interface reading    |
| Temperature    |        °C | DS18B20 sensor reading                    |
| Armed State    |    Status | Indicates arming condition                |
| Ignition State |    Status | Indicates ignition-output state           |
| Time           |    s / ms | Timestamp for plotting and data recording |




