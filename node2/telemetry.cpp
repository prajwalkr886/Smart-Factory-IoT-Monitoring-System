#include "telemetry.h"
#include "network.h"
#include <stdlib.h>
#include <stdio.h>

static char* buf = NULL;
static uint8_t buflen = 0;

static char* f1(float v, char *dst)
{
  return dtostrf(v, 1, 1, dst);
}

void telemetry_init(char* buffer, uint8_t bufLen)
{
  buf = buffer;
  buflen = bufLen;
}

void telemetry_publishTelemetry(const SensorData* data, uint8_t relayState)
{
  char t[8], h[8], l[8];

  f1(data->temperature, t);
  f1(data->humidity, h);


  snprintf(buf, buflen,
    "{\"temperature\":%s,"
    "\"humidity\":%s,"
    "\"ldrValue\":%u,"
    "\"isDark\":%u,"
    "\"motionDetected\":%u,"
    "\"relayState\":%u,"
    "\"doorOpen\":%u,"
    "\"sensorError\":%u}",
    t, h, 
    (unsigned)data->ldrValue,
    (unsigned)data->isDark,
    (unsigned)data->motionDetected,
    (unsigned)relayState,
    (unsigned)data->doorOpen,
    (unsigned)data->sensorError
  );

  network_publish(TOPIC_TELEMETRY, buf, 0);
}