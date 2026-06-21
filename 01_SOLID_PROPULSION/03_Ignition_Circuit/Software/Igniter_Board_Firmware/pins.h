#ifndef PINS_H
#define PINS_H

// Igniter Board Pin Mapping
// Update this file whenever the PCB, wiring, or firmware pin assignment changes.

// Ignition output
#define IGNITION_MOSFET_PIN 26

// HX711 load-cell interface
#define HX711_DOUT_PIN 33
#define HX711_SCK_PIN 32

// Temperature sensor
#define DS18B20_DATA_PIN 14

// Pressure sensor / transmitter analog input
#define PRESSURE_INPUT_PIN 13

#endif
