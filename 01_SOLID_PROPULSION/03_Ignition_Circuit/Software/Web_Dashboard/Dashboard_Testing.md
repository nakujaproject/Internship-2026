# Dashboard Testing Notes

## Overview

This document records how the Nakuja ignition web dashboard should be tested before use during dry runs or static motor tests.

The dashboard should be tested before every important test session to confirm that the interface loads correctly, the WebSocket connection works, telemetry values update, and CSV export functions properly.

## Basic Test Checklist

- [ ] `index.html` opens correctly in the browser.
- [ ] `nakuja_icon.png` loads correctly.
- [ ] Temperature card is visible.
- [ ] Pressure card is visible.
- [ ] Thrust card is visible.
- [ ] Temperature chart loads correctly.
- [ ] Pressure chart loads correctly.
- [ ] Thrust chart loads correctly.
- [ ] Event log is visible.
- [ ] Start Recording button works.
- [ ] Stop Recording button works.
- [ ] Download CSV button works.
- [ ] WebSocket connection works when connected to the trigger board.
- [ ] CSV file contains timestamped values.

## Browser Compatibility

| Browser | Status | Notes |
|---|---|---|
| Google Chrome | To be tested | Recommended browser |
| Microsoft Edge | To be tested | Alternative browser |
| Mozilla Firefox | To be tested | Optional browser |

## Functional Test Cases

| Test | Expected Result |
|---|---|
| Open dashboard offline | Page loads and shows disconnected/offline status |
| Enter correct ESP32 IP address | Dashboard attempts WebSocket connection |
| Connect to trigger board | Status changes to connected |
| Receive valid telemetry packet | Cards and charts update |
| Receive event message | Event log updates |
| Start recording | Stopwatch resets and data recording begins |
| Stop recording | Data recording stops |
| Download CSV | CSV file downloads successfully |
| Refresh page | Dashboard reloads without layout errors |

## Telemetry Test Values

Use sample values such as:

| Variable | Example Value | Unit |
|---|---:|---|
| Temperature | 27.5 | °C |
| Pressure | 101.3 | kPa |
| Thrust | 12.8 | N |
| Ignition armed | false | status |

## Known Issues

| Issue | Status | Notes |
|---|---|---|
| Demo data disabled | Intentional | Real telemetry should be used during actual tests |
| Dashboard depends on CDN libraries | To review | Internet may be required unless libraries are stored locally |
| Pressure calibration | Pending | Final pressure conversion must be verified |
| Brownout effects | Under validation | Power stability should be checked during hardware tests |

## Pre-Test Recommendation

Before a dry run or static test:

1. Open the dashboard.
2. Connect to the trigger board Wi-Fi access point.
3. Enter the ESP32 IP address.
4. Confirm telemetry updates.
5. Start recording.
6. Verify that CSV download works using a short test.
7. Clear old test data before the real test.
8. Record the firmware version and dashboard version used.

## Notes

Dashboard testing validates the user interface and telemetry path only. It does not replace sensor calibration, hardware inspection, ignition safety checks, or approved static-test procedures.
