#ifndef CONFIG_EXAMPLE_H
#define CONFIG_EXAMPLE_H

// Copy this file to config.h before compiling.
// Do not commit private/local config.h files if they contain sensitive values.

// Board identity
#define BOARD_NAME "NAKUJA_TRIGGER_BOARD"

// Dashboard Wi-Fi settings
#define WIFI_AP_SSID "NAKUJA"
#define WIFI_AP_PASSWORD ""

// WebSocket settings
#define WEBSOCKET_PORT 81

// Telemetry forwarding
#define DASHBOARD_UPDATE_INTERVAL_MS 50

#endif
