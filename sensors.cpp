#include "sensors.hpp"
#include <Wire.h>
#include <SensirionI2CSen5x.h>
#include <Adafruit_BME680.h>

SensirionI2CSen5x sen5x;
Adafruit_BME680 bme;

void sensors_init() {
  Wire.begin(21, 22);

  sen5x.begin(Wire);
  sen5x.startMeasurement();

  if (!bme.begin(0x76)) {
    Serial.println("❌ BME688 not found");
  }
}

SensorData sensors_read() {

    SensorData data;   // MUST exist

    uint16_t error = sen5x.readMeasuredValues(
        data.pm1_0,
        data.pm2_5,
        data.pm4_0,
        data.pm10,
        data.humidity,
        data.temperature,
        data.voc,   // float
        data.nox    // float
    );

    if (error) {
        Serial.print("SEN55 read error: ");
        Serial.println(error);
    }

    return data;
}





