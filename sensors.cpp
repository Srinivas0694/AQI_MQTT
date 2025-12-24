#include "sensors.hpp"
#include "config.hpp"

#include <Wire.h>
#include <SensirionI2CSen5x.h>
#include <SensirionI2CScd4x.h>
#include <Adafruit_BME680.h>

SensirionI2CSen5x sen5x;
SensirionI2cScd4x scd4x;      // ✔ correct class name
Adafruit_BME680 bme;

void sensors_init() {
  Wire.begin(SDA_PIN, SCL_PIN);

  // ---------- SEN55 ----------
  sen5x.begin(Wire);
  sen5x.startMeasurement();

  // ---------- BME688 ----------
  if (!bme.begin(0x76)) {
    Serial.println("❌ BME688 not found");
  }

  // ---------- SCD40 ----------
  scd4x.begin(Wire, 0x62);     // ✔ correct signature
  scd4x.stopPeriodicMeasurement();
  delay(1000);
  scd4x.startPeriodicMeasurement();

  Serial.println("✅ SCD40 started");
}

SensorData sensors_read() {
  SensorData data = {};

  // ---------- SEN55 ----------
  sen5x.readMeasuredValues(
    data.pm1_0,
    data.pm2_5,
    data.pm4_0,
    data.pm10,
    data.humidity,
    data.temperature,
    data.voc,
    data.nox
  );

  // ---------- SCD40 ----------
  bool dataReady = false;
  scd4x.getDataReadyStatus(dataReady);   // correct API

  if (dataReady) {
    uint16_t co2;
    float temp, hum;

    if (scd4x.readMeasurement(co2, temp, hum) == 0) {
      if (co2 > 0) {
        data.co2 = co2;
      }
    }
  }

  return data;
}

