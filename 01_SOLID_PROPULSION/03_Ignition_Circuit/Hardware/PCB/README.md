# PCB Documentation

## Overview

This folder contains printed circuit board documentation for the Nakuja Project ignition circuit hardware.

It should include PCB layout files, Gerber files, board images, fabrication notes, and revision records for the igniter board and trigger board.

## Recommended Contents

```text
PCB/
├── README.md
├── Igniter_Board/
├── Trigger_Board/
├── Gerber_Files/
├── PCB_Layout_Images/
└── Fabrication_Notes/
```

## PCB Files to Upload

| File Type                   | Purpose                                                        |
| --------------------------- | -------------------------------------------------------------- |
| Schematic-linked PCB layout | Shows component placement and routing                          |
| Gerber files                | Used for PCB fabrication                                       |
| Drill files                 | Used for PCB hole drilling                                     |
| Top copper image            | Shows top copper routing                                       |
| Bottom copper image         | Shows bottom copper routing                                    |
| Silkscreen image            | Shows labels and component positions                           |
| Board photo                 | Shows the physical fabricated board                            |
| Fabrication notes           | Documents etching, drilling, soldering, or manufacturing steps |

## Board Revision Format

Use clear revision names:

```text
igniter_board_revA
trigger_board_revA
igniter_board_revB
trigger_board_revB
```

## Recommended Revision Table

| Board         | Revision | Date       | Status                      | Notes           |
| ------------- | -------- | ---------- | --------------------------- | --------------- |
| Igniter Board | Rev A    | YYYY-MM-DD | Draft / Fabricated / Tested | Initial version |
| Trigger Board | Rev A    | YYYY-MM-DD | Draft / Fabricated / Tested | Initial version |

## Documentation Notes

For every PCB version, document:

* Board name.
* Revision number.
* Date created.
* Design software used.
* Main changes from previous version.
* Known issues.
* Test status.
* Photos of the final assembled board where available.

## Safety Note

PCB files must match the latest verified schematic and firmware pin mapping. Any mismatch between PCB routing, firmware pins, and wiring diagrams must be corrected before testing.
