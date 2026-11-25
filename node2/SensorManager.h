#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>
#include <stdint.h>
#include "config.h"

typedef struct {
    float    temperature;
    float    humidity;
    uint16_t ldrValue;
    bool     motionDetected;
    bool     doorOpen;
    bool     isDark;
    bool     sensorError;
} SensorData;

typedef struct {
    float         lastTemp;
    float         lastHumidity;
    bool          motionActive;
    unsigned long motionClearTime;
} SensorManager;


void sensor_init  (SensorManager* sm);
void sensor_begin ();
bool sensor_read  (SensorData* out , SensorManager* sm);

#endif