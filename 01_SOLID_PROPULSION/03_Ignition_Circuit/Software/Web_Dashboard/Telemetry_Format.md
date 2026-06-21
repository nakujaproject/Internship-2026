# Telemetry Format — Web Dashboard

## Overview

This document defines the telemetry data format expected by the Nakuja ignition system web dashboard.

The dashboard receives telemetry from the trigger board through a WebSocket connection. The trigger board receives telemetry from the igniter board and forwards it to the dashboard.

## Expected WebSocket Address

```text
ws://<ESP32_IP_ADDRESS>:81
