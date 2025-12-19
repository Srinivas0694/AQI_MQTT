#ifndef SENSORS_HPP
#define SENSORS_HPP

#include <Arduino.h>

typedef struct {
    float pm1_0;
    float pm2_5;
    float pm4_0;
    float pm10;
    float temperature;
    float humidity;
    float voc;   // ✅ MUST be float (your library)
    float nox;   // ✅ MUST be float
} SensorData;

void sensors_init();
SensorData sensors_read();

#endif
