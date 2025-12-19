#include <Arduino.h>
#include "sensors.hpp"
#include "display.hpp"
#include "aws_iot.hpp"

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("ESP32 Air Quality Project Started");

  sensors_init();
  Serial.println("Sensors initialized");

  display_init();
  Serial.println("OLED initialized");

  aws_init();
  Serial.println("AWS IoT connected");
}

void loop() {
  SensorData data = sensors_read();

 Serial.println("---- OLED DATA ----");
 Serial.print("PM1.0 : "); Serial.println(data.pm1_0);
 Serial.print("PM2.5 : "); Serial.println(data.pm2_5);
 Serial.print("PM4.0 : "); Serial.println(data.pm4_0);
 Serial.print("PM10  : "); Serial.println(data.pm10);
 Serial.print("Temp  : "); Serial.println(data.temperature);
 Serial.print("Hum   : "); Serial.println(data.humidity);
 Serial.print("VOC   : "); Serial.println(data.voc);
 Serial.print("NOx   : "); Serial.println(data.nox);


  display_show(data);
  aws_publish(data);
  aws_loop();

  delay(5000);
}

