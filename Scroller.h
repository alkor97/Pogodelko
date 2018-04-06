
#pragma once

#include "Display.h"

class Scroller {
  public:
    void setup(Display& display, uint8_t newY) {
      position = display.width();
      y = newY;
    }

    void setText(const String& newText) {
      text = newText;
    }

    void show(Display& display) {
      display.setCursor(position, y);
      display.print(text);

      if (position == -text.length() * 6) {
        position = display.width();
      } else {
        --position;
      }
    }
  private:
    uint8_t y;
    int position;
    String text;
};

