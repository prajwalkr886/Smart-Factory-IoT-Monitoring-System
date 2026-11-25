#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>

// Pin definitions
#define PIN_LED_RED     5
#define PIN_LED_GREEN   6
#define PIN_LED_YELLOW  7
#define PIN_RELAY       8

// Function declarations
void actuators_begin(void);
void actuators_updateStatusLEDs(uint8_t mqttConnected, uint8_t sensorError);
void actuators_setRelay(uint8_t on);
uint8_t actuators_getRelayState(void);

#endif