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
  f1(data->lm35Temp, l);

  snprintf(buf, buflen,
    "{\"temperature\":%s,"
    "\"humidity\":%s,"
    "\"lm35Temp\":%s,"
    "\"vibration\":%u,"
    "\"machineStatus\":%u,"
    "\"relayState\":%u,"
    "\"sensorError\":%u}",
    t, h, l,
    (unsigned)data->vibration,
    (unsigned)data->machineStatus,
    (unsigned)relayState,
    (unsigned)data->sensorError
  );

  network_publish(TOPIC_TELEMETRY, buf, 0);
}