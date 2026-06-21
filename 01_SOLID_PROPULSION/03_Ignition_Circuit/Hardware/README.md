# Hardware — Ignition Circuit

## Overview

This folder contains the hardware documentation for the Nakuja Project ignition and real-time telemetry system. It includes circuit diagrams, PCB files, wiring diagrams, pin mappings, power-system notes, bill of materials, and reference photos.

The hardware system is divided into two main modules:

1. Igniter Circuit Board
2. Trigger Circuit Board

The igniter board is placed near the motor or static test stand, while the trigger board is operated from a safe distance.

## Recommended Folder Structure

```text
Hardware/
├── README.md
├── Schematics/
├── PCB/
├── Wiring_Diagrams/
├── Photos/
├── BOM.md
└── Pin_Mapping.md
```

## Main Hardware Modules

| Module                | Location               | Purpose                                                               |
| --------------------- | ---------------------- | --------------------------------------------------------------------- |
| Igniter Circuit Board | Near static test stand | Sensor reading, telemetry transmission, ignition-output control       |
| Trigger Circuit Board | Operator side          | Command input, telemetry reception, dashboard link, operator feedback |
| Sensor Interfaces     | Test-stand side        | Thrust, pressure, and temperature measurement                         |
| Power System          | Both boards            | Provides regulated voltage to electronics and sensors                 |

## Igniter Circuit Board

The igniter board handles test-stand-side sensing and output control.

Main hardware functions:

* Interface with the load cell through the HX711 module.
* Interface with the DS18B20 temperature sensor.
* Interface with the pressure transmitter circuit.
* Control the MOSFET-based ignition-output stage.
* Send telemetry to the trigger board.
* Receive wireless command signals from the trigger board.

Recommended documentation:

```text
Igniter_Board/
├── schematic.pdf
├── pcb_layout.png
├── wiring_diagram.png
├── board_photo.jpg
└── notes.md
```

## Trigger Circuit Board

The trigger board handles the operator-side control and communication functions.

Main hardware functions:

* Provide operator command input.
* Give status feedback through buzzer, LED, or display output.
* Receive telemetry from the igniter board.
* Support Wi-Fi and WebSocket communication to the dashboard.
* Maintain operator-side separation from the test stand.

Recommended documentation:

```text
Trigger_Board/
├── schematic.pdf
├── pcb_layout.png
├── wiring_diagram.png
├── board_photo.jpg
└── notes.md
```

## Main Components

| Component                      | Purpose                                    |
| ------------------------------ | ------------------------------------------ |
| ESP32                          | Main controller for both boards            |
| HX711                          | Load-cell signal acquisition               |
| Load cell                      | Thrust measurement                         |
| DS18B20                        | Temperature measurement                    |
| Pressure transmitter/interface | Chamber pressure measurement               |
| IRFZ44N MOSFET                 | Ignition-output switching                  |
| Buck converter                 | Step-down voltage regulation               |
| Boost converter                | Pressure transmitter supply where required |
| XT60 / XT30 connectors         | Secure power connection                    |
| JST connectors                 | Secure sensor connections                  |
| Buzzer                         | Operator feedback                          |
| Status LED                     | Visual indication                          |

## Power System

The hardware should include clear documentation of the power path.

Document the following:

* Main battery voltage.
* Regulated logic voltage.
* ESP32 supply voltage.
* Sensor supply voltage.
* Pressure transmitter supply voltage.
* Ground reference connections.
* Connector type and polarity.
* Fuse or protection method where used.
* Brownout issues and mitigation steps.

## Sensor Interfaces

### Load Cell and HX711

The load cell and HX711 subsystem is used for thrust measurement. The hardware documentation should include:

* Load-cell wiring.
* HX711 wiring.
* HX711 sampling-rate configuration.
* Calibration connection notes.
* Mechanical mounting reference where available.

### DS18B20 Temperature Sensor

The DS18B20 subsystem is used for temperature measurement. The hardware documentation should include:

* Sensor wiring.
* Pull-up resistor value where used.
* Connector type.
* Physical mounting location.

### Pressure Transmitter Interface

The pressure transmitter/interface is used for chamber pressure measurement. The hardware documentation should include:

* Pressure transmitter wiring.
* Supply voltage.
* Current-to-voltage conversion circuit.
* ESP32 analog input connection.
* Resistor value used for conversion.
* Expected voltage range.
* Calibration notes.

## PCB Documentation

For each PCB revision, include:

| File              | Description                           |
| ----------------- | ------------------------------------- |
| Schematic         | Circuit-level design                  |
| PCB layout        | Board routing and component placement |
| Gerber files      | Fabrication files                     |
| Board photos      | Physical reference                    |
| Revision notes    | What changed between versions         |
| Test notes        | What was verified                     |

## Pin Mapping

Create or update `Pin_Mapping.md` with a table such as:

| Function            |        ESP32 Pin | Board   | Notes                           |
| ------------------- | ---------------: | ------- | ------------------------------- |
| MOSFET gate         |           GPIO26 | Igniter | Ignition-output control         |
| HX711 DOUT          |           GPIO33 | Igniter | Load-cell data                  |
| HX711 SCK           |           GPIO32 | Igniter | Load-cell clock                 |
| DS18B20 data        |           GPIO14 | Igniter | Temperature input               |
| Pressure input      |           GPIO13 | Igniter | Analog pressure signal          |
| Buzzer              | To be documented | Trigger | Operator feedback               |
| Status input/button | To be documented | Trigger | Operator command or state input |

## Hardware Documentation Rules

When adding hardware files:

1. Use clear file names.
2. Separate schematics, PCB files, wiring diagrams, and photos.
3. Label every board revision.
4. Add notes for tested and untested circuits.
5. Document connector polarity.
6. Document voltage levels.
7. Document sensor pinouts.
8. Keep photos compressed but clear.
9. Do not upload unexplained Gerber or schematic files.
10. Add a short note when replacing or modifying a component.

## Current Status

| Area                           | Status                                 |
| ------------------------------ | -------------------------------------- |
| Igniter board hardware         | In development / testing               |
| Trigger board hardware         | In development / testing               |
| Load-cell interface            | Integrated                             |
| Temperature sensor interface   | Integrated                             |
| Pressure transmitter interface | Requires final validation              |
| Power regulation               | Requires brownout validation           |
| PCB documentation              | To be updated with final board files   |
| Wiring documentation           | To be completed with labelled diagrams |
