#include "actuator.h"

// Global relay state
static uint8_t relay_status = 0;

void actuators_begin(void)
{
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);

  // Initial state
  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_RELAY, LOW);
}

void actuators_updateStatusLEDs(uint8_t mqttConnected, uint8_t sensorError)
{
  // Green LED → MQTT status
  digitalWrite(PIN_LED_GREEN, mqttConnected ? HIGH : LOW);

  // Yellow LED → Sensor error
  digitalWrite(PIN_LED_YELLOW, sensorError ? HIGH : LOW);
}

void actuators_setRelay(uint8_t on)
{
  relay_status = on;
  digitalWrite(PIN_RELAY, on ? HIGH : LOW);
}

uint8_t actuators_getRelayState(void)
{
  return relay_status;
}