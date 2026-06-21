#ifndef CONFIG_EXAMPLE_H
#define CONFIG_EXAMPLE_H

// Copy this file to config.h before compiling.
// Do not commit private/local config.h files if they contain sensitive values.

// Board identity
#define BOARD_NAME "NAKUJA_TRIGGER_BOARD"

// Dashboard Wi-Fi access point
#define WIFI_AP_SSID "NAKUJA"
#define WIFI_AP_PASSWORD "12345678"

// WebSocket settings
#define WEBSOCKET_PORT 81

// LCD configuration
#define LCD_I2C_ADDRESS 0x3F
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Dashboard update settings
#define LCD_UPDATE_INTERVAL_MS 250

#endif
