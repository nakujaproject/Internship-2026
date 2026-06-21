# Trigger Board Firmware

## Overview

This folder contains the ESP32 firmware for the trigger-side board of the Nakuja Project ignition and real-time telemetry system.

The trigger board is positioned with the operator at a safe distance. It sends ignition commands, receives telemetry from the igniter board, provides operator feedback, and streams data to the web dashboard.

## Main Responsibilities

* Send ignition commands to the igniter board.
* Receive telemetry from the igniter board through ESP-NOW.
* Create a local Wi-Fi access point for dashboard connection.
* Run a WebSocket server for real-time dashboard communication.
* Forward telemetry values to the dashboard.
* Provide operator feedback using buzzer, LED, LCD, or other indicators.
* Support safe operator-side control.

## Main Interfaces

| Function                     | Device/Interface       | Notes                                 |
| ---------------------------- | ---------------------- | ------------------------------------- |
| Board-to-board communication | ESP-NOW                | Receives telemetry and sends commands |
| Dashboard connection         | Wi-Fi access point     | Laptop connects locally               |
| Dashboard streaming          | WebSocket server       | Sends live telemetry                  |
| Operator feedback            | Buzzer / LED / display | Shows status and alerts               |
| Operator command             | Push button / switch   | Used for controlled command input     |

## Recommended Folder Contents

```text
Trigger_Board_Firmware/
├── README.md
├── main.ino
├── config.example.h
├── pins.h
└── libraries.md
```

## Firmware Logic

The firmware should generally follow this sequence:

1. Initialize pins and feedback devices.
2. Initialize ESP-NOW communication.
3. Create the Wi-Fi access point.
4. Start the WebSocket server.
5. Receive telemetry from the igniter board.
6. Forward telemetry to the dashboard.
7. Monitor operator command input.
8. Send ignition command only when required.
9. Report connection and system-status changes.

## Communication Role

```text
Igniter Board
     ↓
ESP-NOW
     ↓
Trigger Board
     ↓
Wi-Fi + WebSocket
     ↓
Web Dashboard
```

## Documentation Requirements

When firmware is uploaded, include:

* Firmware version.
* Required libraries.
* Board type used.
* Pin mapping.
* Wi-Fi access point name.
* WebSocket port.
* Upload instructions.
* Known issues.
* Test notes.

## Safety Note

The trigger board should not send an ignition command accidentally. Operator input, arming status, communication status, and system state should be handled clearly in the firmware.
