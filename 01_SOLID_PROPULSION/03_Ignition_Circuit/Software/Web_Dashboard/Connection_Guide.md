# Dashboard Connection Guide

## Overview

This document explains how to connect the Nakuja ignition web dashboard to the ESP32 trigger board.

The dashboard receives telemetry through a WebSocket connection from the trigger board. The trigger board receives telemetry from the igniter board and forwards it to the browser dashboard.

## Connection Steps

1. Power the trigger board.
2. Confirm that the trigger board has created its Wi-Fi access point.
3. Connect the laptop or tablet to the trigger board Wi-Fi network.
4. Open the dashboard file in a browser:

```text
index.html
```

5. Enter the ESP32 IP address in the dashboard input field.
6. Click **Connect**.
7. Confirm that the dashboard status changes to **Connected**.
8. Confirm that temperature, pressure, and thrust values update.

## Default WebSocket Settings

| Item                     | Value                 |
| ------------------------ | --------------------- |
| Default ESP32 IP address | `192.168.4.1`         |
| WebSocket port           | `81`                  |
| WebSocket address        | `ws://192.168.4.1:81` |
| Dashboard file           | `index.html`          |
| Logo file                | `nakuja_icon.png`     |

## Expected Connection Flow

```text
Igniter Board
     ↓
ESP-NOW
     ↓
Trigger Board
     ↓
Wi-Fi Access Point
     ↓
WebSocket
     ↓
Browser Dashboard
```

## Successful Connection Indicators

A successful connection should show:

* Dashboard status changes from **Disconnected** to **Connected**.
* System status changes to **Operational**.
* Temperature value updates.
* Pressure value updates.
* Thrust value updates.
* Event log records the connection event.

## Troubleshooting

| Problem                     | Possible Cause                  | Recommended Check                                               |
| --------------------------- | ------------------------------- | --------------------------------------------------------------- |
| Dashboard does not connect  | Wrong IP address                | Confirm the ESP32 IP address                                    |
| Status remains disconnected | WebSocket server is not running | Check trigger board firmware                                    |
| Values remain zero          | No telemetry packets received   | Check ESP-NOW communication                                     |
| Charts do not update        | Invalid telemetry format        | Check JSON field names                                          |
| CSV has no data             | Recording was not started       | Click **Start Recording** before test                           |
| Logo does not show          | Missing image file              | Confirm `nakuja_icon.png` is in the same folder as `index.html` |
| Browser shows errors        | Missing internet/CDN access     | Check Chart.js loading or use offline libraries later           |

## Notes

* The laptop must be connected to the ESP32 trigger board access point before the dashboard can connect.
* The WebSocket server is expected to run on port `81`.
* The dashboard is a monitoring and recording interface only.
* It does not replace firmware safety logic, physical safety procedures, or approved test checklists.
