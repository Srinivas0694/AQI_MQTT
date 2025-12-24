#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "display.hpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void display_init() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while (1);
  }

  display.setRotation(1);   // ✅ PORTRAIT MODE
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.println("DEVICE 1");
  display.display();
}

void display_show(const SensorData &data) {
    display.clearDisplay();
    display.setRotation(1);           // Portrait
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    int y = 0;
    int lineGap = 10;                  // controls spacing

    display.setCursor(0, y);
    display.println("DEVICE 1");
    y += lineGap + 2;

    display.println("----------");
    y += lineGap;

    display.setCursor(0, y);
    display.print("PM1.0:"); display.println(data.pm1_0); y += lineGap;

    display.setCursor(0, y);
    display.print("PM2.5:"); display.println(data.pm2_5); y += lineGap;
    
    display.setCursor(0, y);
    display.print("PM4.0:"); display.println(data.pm4_0); y += lineGap;

    display.setCursor(0, y);
    display.print("PM10 :"); display.println(data.pm10); y += lineGap;

    display.setCursor(0, y);
    display.print("Temp:"); display.print(data.temperature); display.println(" C"); y += lineGap;

    display.setCursor(0, y);
    display.print("RH:"); display.print(data.humidity); display.println(" %"); y += lineGap;

    display.setCursor(0, y);
    display.print("VOC:"); display.println(data.voc); y += lineGap;

    display.setCursor(0, y);
    display.print("NOx:"); display.println(data.nox); y += lineGap;

    display.setCursor(0, y);
    display.print("CO2:"); display.print(data.co2); display.println(" ppm");

    display.display();
}



