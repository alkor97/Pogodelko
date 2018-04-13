
#pragma once

#include "Display.h"

class HorizontalScroller {
  public:
    void setup(uint8_t y = 0, int16_t screenWidth = 64) {
      anchorX = 0;
      anchorY = y;
      screenWidth = screenWidth;
    }

    void show(Display& display) {
      display.setCursor(anchorX, anchorY);
      const int16_t contentWidth = render(display, anchorX, anchorY);
      if (anchorX <= -contentWidth) {
        anchorX = display.width();
      } else {
        --anchorX;
      }
    }

  protected:
    virtual int16_t render(Display& display, const int16_t x, const int16_t y) = 0;

  private:
    int16_t anchorX;
    int16_t anchorY;
    int16_t screenWidth;
};

class TextScroller : public HorizontalScroller {
  public:
    void setup(Display& display, uint8_t newY) {
      ((HorizontalScroller*) this)->setup((uint8_t)newY, display.width());
    }

    void setText(const String& newText) {
      text = newText;
    }

    int16_t render(Display& display, const int16_t x, const int16_t y) {
      display.setCursor(x, y);
      display.print(text);
      return text.length() * 6;
    }
  private:
    String text;
};

