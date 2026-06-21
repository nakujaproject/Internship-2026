## File: `Schematics/README.md`

# Schematics

## Overview

This folder contains circuit schematics for the Nakuja Project ignition system hardware.

The schematics should document the electrical connections for the igniter board, trigger board, sensor interfaces, power regulation stage, and ignition-output switching circuit.

## Recommended Contents

* Igniter board schematic.
* Trigger board schematic.
* Power regulation schematic.
* HX711 load-cell interface schematic.
* DS18B20 temperature sensor interface.
* Pressure transmitter/interface circuit.
* MOSFET ignition-output switching circuit.
* Status LED and buzzer connections.

## Documentation Notes

Each schematic should clearly show:

* Component labels.
* Connector names.
* Voltage levels.
* Ground reference.
* ESP32 pin connections.
* Sensor wiring.
* Power input and output paths.
* Revision number and date.

---

## File: `PCB/README.md`

# PCB

## Overview

This folder contains printed circuit board documentation for the ignition system.

It should include PCB layout files, Gerber files, board images, fabrication notes, and revision history for both the igniter board and trigger board.

## Recommended Contents

* PCB layout screenshots.
* Gerber files.
* Board fabrication files.
* Etching or manufacturing notes.
* Component placement diagrams.
* Top and bottom copper layer images.
* Board revision notes.
* Photos of assembled PCBs.

## Documentation Notes

Each PCB revision should include:

| Item       | Description                            |
| ---------- | -------------------------------------- |
| Board name | Igniter board or trigger board         |
| Revision   | Rev A, Rev B, etc.                     |
| Date       | Date uploaded or fabricated            |
| Status     | Draft, fabricated, tested, or archived |
| Notes      | Main changes or known issues           |

---

## File: `Wiring_Diagrams/README.md`

# Wiring Diagrams

## Overview

This folder contains wiring diagrams for the ignition system.

The wiring diagrams should make it easy for a team member to connect the boards, sensors, power supply, and dashboard communication hardware correctly.

## Recommended Contents

* Full system wiring diagram.
* Igniter board wiring diagram.
* Trigger board wiring diagram.
* Load-cell and HX711 wiring.
* DS18B20 wiring.
* Pressure transmitter/interface wiring.
* Power wiring.
* Connector pinout diagrams.

## Documentation Notes

Each wiring diagram should clearly show:

* Connector names.
* Pin numbers.
* Wire colors where applicable.
* Voltage level.
* Ground connections.
* Signal direction.
* Sensor polarity.
* Power polarity.
* Safety-related connections.

---

## File: `Photos/README.md`

# Photos

## Overview

This folder contains reference photos for the ignition system hardware.

Photos should help future team members understand the physical assembly, wiring, PCB layout, and test setup.

## Recommended Contents

* Igniter board photos.
* Trigger board photos.
* PCB fabrication photos.
* Wiring photos.
* Sensor connection photos.
* Dashboard setup photos.
* Static-test setup photos where appropriate.

## Photo Naming Format

Use clear names such as:

```text
igniter_board_revA_top_view.jpg
trigger_board_revA_wiring.jpg
hx711_load_cell_connection.jpg
pressure_interface_test_setup.jpg
pcb_etching_process_revA.jpg
```

## Documentation Notes

Avoid uploading unclear or duplicate photos. Each important photo should be labelled or accompanied by a short note explaining what it shows.
