
## Purpose

This folder serves as the main documentation and development space for the ignition subsystem. It should help future team members understand, reproduce, test, maintain, and improve the ignition system.

The folder should contain:

* ESP32 firmware for the igniter board.
* ESP32 firmware for the trigger board.
* Web dashboard source files.
* Circuit diagrams and PCB files.
* Pin mappings and wiring documentation.
* Sensor calibration notes.
* Static-test and dry-run telemetry data.
* Dashboard screenshots and CSV logs.
* Safety checklists and operating notes.
* Relevant progress reports and technical summaries.

## System Architecture

The ignition system is divided into two main hardware modules:

| Module                | Location                                        | Main Function                                                                  |
| --------------------- | ----------------------------------------------- | ------------------------------------------------------------------------------ |
| Igniter Circuit Board | Near the motor or static test stand             | Reads sensors, controls the ignition-output circuit, and sends telemetry       |
| Trigger Circuit Board | Operator side / safe distance                   | Sends ignition commands, receives telemetry, and streams data to the dashboard |
| Web Dashboard         | Laptop or tablet connected to the trigger board | Displays real-time telemetry, logs events, and exports CSV data                |

## Igniter Circuit Board

The igniter board is the test-stand-side module. It handles sensor acquisition, ignition-output control, and telemetry transmission.

Main functions:

* Reads thrust data from a load cell through the HX711 module.
* Reads temperature using the DS18B20 temperature sensor.
* Interfaces with the pressure transmitter circuit for chamber pressure monitoring.
* Receives wireless commands from the trigger board.
* Controls the MOSFET-based ignition-output circuit.
* Limits the ignition-output duration using firmware safety logic.
* Sends telemetry data to the trigger board.

Main components:

| Component                      | Purpose                                     |
| ------------------------------ | ------------------------------------------- |
| ESP32                          | Main controller                             |
| HX711                          | Load-cell signal acquisition                |
| Load cell                      | Thrust measurement                          |
| DS18B20                        | Temperature measurement                     |
| Pressure transmitter/interface | Chamber pressure measurement                |
| IRFZ44N MOSFET                 | Ignition-output switching                   |
| Power regulation circuit       | Stable supply for logic and sensor circuits |

## Trigger Circuit Board

The trigger board is the operator-side module. It acts as the control and communication bridge between the igniter board and the dashboard.

Main functions:

* Sends ignition commands to the igniter board.
* Receives telemetry from the igniter board through ESP-NOW.
* Creates a local Wi-Fi access point.
* Runs a WebSocket server for dashboard communication.
* Provides operator feedback using indicators such as buzzer, status LED, or display output.
* Supports safer test operation by keeping the operator away from the test stand.

## Web Dashboard

The dashboard is a browser-based interface for real-time test monitoring and data recording.

Main functions:

* Displays thrust, pressure, and temperature values.
* Shows telemetry trends using graphs.
* Displays system and connection status.
* Logs important events such as arming, disconnection, and ignition status.
* Allows recording to be started and stopped.
* Exports telemetry as timestamped CSV files for later analysis.

The dashboard is developed using:

| Technology | Use                                                        |
| ---------- | ---------------------------------------------------------- |
| HTML       | Dashboard structure                                        |
| CSS        | Styling and layout                                         |
| JavaScript | Data handling, plotting, event logging, and CSV export     |
| WebSocket  | Real-time telemetry communication                          |
| Node.js    | Dashboard testing or telemetry simulation where applicable |

## Communication Flow

The system uses two communication layers:

| Link                          | Method                         | Purpose                                            |
| ----------------------------- | ------------------------------ | -------------------------------------------------- |
| Igniter board ↔ Trigger board | ESP-NOW                        | Board-to-board command and telemetry communication |
| Trigger board ↔ Dashboard     | Wi-Fi access point + WebSocket | Real-time dashboard streaming                      |

General data flow:

```text
Sensors
   ↓
Igniter Circuit Board
   ↓
ESP-NOW
   ↓
Trigger Circuit Board
   ↓
Wi-Fi + WebSocket
   ↓
Web Dashboard
   ↓
CSV Export
```

## Telemetry Variables

| Variable       |      Unit | Source                         |
| -------------- | --------: | ------------------------------ |
| Thrust         |         N | Load cell + HX711              |
| Pressure       |       bar | Pressure transmitter           |
| Temperature    |        °C | DS18B20                        |
| Armed State    |    Status | Firmware logic                 |
| Ignition State |    Status | Firmware logic                 |
| Time           |    s / ms | ESP32 or dashboard timestamp   |

## Sensor and Data Acquisition

### Load Cell and HX711

The load cell is used to measure thrust during static testing. The HX711 converts the small load-cell signal into digital data that can be processed by the ESP32.

The HX711 sampling rate was improved to increase the number of useful data points during short static-test burns. This improves thrust-curve resolution and helps with later comparison against simulation results.

### Temperature Sensor

The DS18B20 digital temperature sensor is used for temperature measurement. It provides a digital reading and reduces the need for analog signal conditioning.

### Pressure Transmitter Interface

The pressure measurement system is intended to monitor chamber pressure during static testing. Since the ESP32 reads voltage, the pressure transmitter signal must be conditioned into a safe analog voltage range before being connected to the ESP32 analog input.

Pressure data is important for understanding combustion behavior, validating simulations, and supporting future motor scaling decisions.

## Safety Logic

The ignition system is safety-critical. The firmware and operating procedure must ensure that ignition only occurs under controlled conditions.

Core safety features:

* Remote operator-side command.
* Wireless separation between operator and test stand.
* Arming logic before ignition.
* Timed ignition-output window.
* Status feedback through the dashboard and indicators.
* Telemetry confirmation before test operation.
* Data recording for post-test review.
* Documentation of abnormal behavior before further testing.

## Software Folder

The `Software/` folder should contain all firmware and dashboard-related files.

Recommended structure:

```text
Software/
├── Igniter_Board_Firmware/
├── Trigger_Board_Firmware/
├── Web_Dashboard/
└── Simulation_or_Test_Tools/
```

Recommended contents:

* ESP32 igniter firmware.
* ESP32 trigger firmware.
* Dashboard HTML, CSS, and JavaScript files.
* WebSocket or Node.js simulation tools.
* Required libraries.
* Upload instructions.
* Firmware notes.
* Dashboard screenshots.
* Sample test data.

## Hardware Folder

The `Hardware/` folder should contain all physical design and electronics documentation.

Recommended structure:

```text
Hardware/
├── Schematics/
├── PCB/
├── Wiring_Diagrams/
├── Photos/
├── BOM.md
└── Pin_Mapping.md
```


## Development Status

| Area                           | Status                                           |
| ------------------------------ | ------------------------------------------------ |
| Igniter board firmware         | In development / testing                         |
| Trigger board firmware         | In development / testing                         |
| Web dashboard                  | Developed for real-time telemetry visualization  |
| ESP-NOW communication          | Implemented for board-to-board communication     |
| WebSocket communication        | Implemented for dashboard streaming              |
| HX711 load-cell acquisition    | Improved for higher sampling-rate thrust capture |
| DS18B20 temperature sensing    | Integrated                                       |
| Pressure transmitter interface | Requires final validation and calibration        |
| Power stability                | Brownout mitigation requires final validation    |
| CSV export                     | Implemented in dashboard workflow                |
| Static-test validation         | To be updated after each test campaign           |

## Repository Scope

This folder covers:

* Ignition system electronics.
* ESP32 firmware.
* Wireless communication.
* Web dashboard development.
* Sensor interfacing.
* Telemetry logging.
* Calibration notes.
* Hardware documentation.
* Test data.
* Safety checklists.


## Safety Notice

All ignition-system testing must be conducted only under approved Nakuja Project procedures, supervision, safe-distance operation, and proper pre-test checks.

This repository folder is for electronics, firmware, telemetry, calibration, data logging, and safety documentation only.
