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
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  int x = 0;
  int y = 0;
  int lineGap = 12;

  display.setCursor(x, y);
  display.println("DEVICE 1");

  y += lineGap;
  display.drawLine(0, y, 64, y, SSD1306_WHITE);

  y += lineGap;
  display.setCursor(x, y);
  display.printf("PM1.0:%.1f", data.pm1_0);

  y += lineGap;
  display.setCursor(x, y);
  display.printf("PM2.5:%.1f", data.pm2_5);

  y += lineGap;
  display.setCursor(x, y);
  display.printf("PM4.0:%.1f", data.pm4_0);

  y += lineGap;
  display.setCursor(x, y);
  display.printf("PM10: %.1f", data.pm10);

  y += lineGap;
  display.setCursor(x, y);
  display.printf("Temp:%.1fC", data.temperature);

  y += lineGap;
  display.setCursor(x, y);
  display.printf("RH:%.0f %%", data.humidity);

  y += lineGap;
  display.setCursor(x, y);
  display.print("VOC: ");
  display.print((int)data.voc);

  y += lineGap;
  display.setCursor(0, y);
  display.print("NOx: ");
  display.print((int)data.nox);


  display.display();
}


