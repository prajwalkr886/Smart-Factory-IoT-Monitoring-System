#include "actuator.h"

#define BLINK_INTERVAL 500

static uint8_t relay_status = 0;
static uint8_t blinkstate = 0;
static unsigned long lastBlinkTime = 0;

void actuators_begin(void)   
{
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);

  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_YELLOW, LOW);
  digitalWrite(PIN_RELAY, LOW);   
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

void actuators_updateStatusLEDs(uint8_t mqttConnected, uint8_t sensorError)
{
  if (!mqttConnected) {
    digitalWrite(PIN_LED_GREEN, LOW);
    digitalWrite(PIN_LED_YELLOW, LOW);

    
    digitalWrite(PIN_RELAY, relay_status ? HIGH : LOW);
    return;
  }

  if (sensorError) {
    digitalWrite(PIN_LED_GREEN, HIGH);

    unsigned long now = millis();
    if (now - lastBlinkTime > BLINK_INTERVAL) {
      lastBlinkTime = now;
      blinkstate = !blinkstate;
      digitalWrite(PIN_LED_YELLOW, blinkstate ? HIGH : LOW);
    }
  }
  else {
    digitalWrite(PIN_LED_GREEN, HIGH);
    digitalWrite(PIN_LED_YELLOW, LOW);
  }
}