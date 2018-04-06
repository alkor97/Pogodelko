
#pragma once

#include <SPI.h>              // OLED
#include <Wire.h>             // OLED comunication
#include <Adafruit_GFX.h>     // OLED Core graphics library
#include <Adafruit_SSD1306.h> // OLED Hardware-specific library

///////////////////////////////////////////// OLED PART
// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0

class Display : public Adafruit_SSD1306 {
  public:
    Display() : Adafruit_SSD1306(OLED_RESET) {}
    void init() {
      begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
      setTextColor(WHITE);
      setTextSize(1);
      setCursor(0, 0);
      clear();
    }

    void clear(int color = BLACK) {
      drawPixel(1, 1, color);
      display();
      clearDisplay();
      setCursor(0, 0);
    }
};

#if (SSD1306_LCDHEIGHT != 48)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
///////////////////////////////////////////// OLED PART

