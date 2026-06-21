# Wiring Diagrams

## Overview

This folder contains wiring diagrams for the Nakuja Project ignition circuit hardware.

The wiring diagrams should help team members correctly connect the igniter board, trigger board, sensors, power supply, and dashboard communication setup.

## Recommended Contents

```text
Wiring_Diagrams/
├── README.md
├── Full_System_Wiring/
├── Igniter_Board_Wiring/
├── Trigger_Board_Wiring/
├── Sensor_Wiring/
└── Power_Wiring/
```

## Diagrams to Include

| Diagram                               | Purpose                                           |
| ------------------------------------- | ------------------------------------------------- |
| Full system wiring diagram            | Shows the complete ignition system connection     |
| Igniter board wiring diagram          | Shows test-stand-side wiring                      |
| Trigger board wiring diagram          | Shows operator-side wiring                        |
| HX711 and load-cell wiring            | Shows thrust measurement connection               |
| DS18B20 wiring                        | Shows temperature sensor connection               |
| Pressure transmitter/interface wiring | Shows pressure measurement connection             |
| Power wiring diagram                  | Shows battery, regulators, and board supply paths |
| Connector pinout diagram              | Shows XT, JST, and board connector wiring         |

## Wiring Documentation Requirements

Each wiring diagram should clearly show:

* Component names.
* Connector names.
* Pin numbers.
* Wire colors where applicable.
* Voltage levels.
* Ground connections.
* Signal direction.
* Power polarity.
* Sensor polarity.
* ESP32 pin connections.
* Revision date.

## Recommended Naming Format

```text
full_system_wiring_revA.png
igniter_board_wiring_revA.png
trigger_board_wiring_revA.png
hx711_load_cell_wiring_revA.png
pressure_interface_wiring_revA.png
power_distribution_wiring_revA.png
```

## Important Notes

* The wiring diagram must match the schematic.
* The wiring diagram must match `Pin_Mapping.md`.
* Any changed wire, connector, or ESP32 pin must be updated here.
* Sensor wiring should be labelled clearly to avoid reverse connection.
* Power and ground wiring should be shown clearly to reduce brownout and grounding issues.
