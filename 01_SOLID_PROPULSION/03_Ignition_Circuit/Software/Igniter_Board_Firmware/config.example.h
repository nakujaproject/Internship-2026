#ifndef CONFIG_EXAMPLE_H
#define CONFIG_EXAMPLE_H

// Copy this file to config.h before compiling.
// Do not commit private/local config.h files if they contain sensitive values.

// Board identity
#define BOARD_NAME "NAKUJA_IGNITER_BOARD"

// Timing settings
#define IGNITION_WINDOW_MS 15000

// Load-cell calibration placeholder
#define LOAD_CELL_CALIBRATION_FACTOR 1.0

// Pressure sensor calibration placeholders
#define PRESSURE_SENSOR_OFFSET 0.0
#define PRESSURE_SENSOR_SCALE 1.0

// Telemetry settings
#define TELEMETRY_INTERVAL_MS 50

#endif
