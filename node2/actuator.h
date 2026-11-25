#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <Arduino.h>
#include <stdint.h>


#define PIN_LED_GREEN   2
#define PIN_LED_YELLOW  3
#define PIN_RELAY       4

void actuators_begin(void);
void actuators_setRelay(uint8_t on);
uint8_t actuators_getRelayState(void);
void actuators_updateStatusLEDs(uint8_t mqttConnected, uint8_t sensorError);

#endif