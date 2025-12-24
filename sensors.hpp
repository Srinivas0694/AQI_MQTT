#ifndef SENSORS_HPP
#define SENSORS_HPP

#include <stdint.h>

typedef struct {
  float pm1_0;
  float pm2_5;
  float pm4_0;
  float pm10;
  float temperature;
  float humidity;
  float voc;
  float nox;
  uint16_t co2;     // ✅ SCD40 CO₂ only
} SensorData;

void sensors_init();
SensorData sensors_read();

#endif
