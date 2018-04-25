
#pragma once

#include "WeatherProvider.h"

namespace symbols {
namespace arrows {
const uint8_t N[] PROGMEM = {
  B00010000,
  B00111000,
  B01010100,
  B10010010,
  B00010000,
  B00010000,
  B00010000,
  B00000000
};

const uint8_t NE[] PROGMEM = {
  B00111110,
  B00000110,
  B00001010,
  B00010010,
  B00100010,
  B01000000,
  B10000000,
  B00000000,
};

const uint8_t E[] PROGMEM = {
  B00010000,
  B00001000,
  B00000100,
  B11111110,
  B00000100,
  B00001000,
  B00010000,
  B00000000,
};

const uint8_t SE[] PROGMEM = {
  B10000000,
  B01000000,
  B00100010,
  B00010010,
  B00001010,
  B00000110,
  B00111110,
  B00000000,
};

const uint8_t S[] PROGMEM = {
  B00010000,
  B00010000,
  B00010000,
  B10010010,
  B01010100,
  B00111000,
  B00010000,
  B00000000,
};

const uint8_t SW[] PROGMEM = {
  B00000010,
  B00000100,
  B10001000,
  B10010000,
  B10100000,
  B11000000,
  B11111000,
  B00000000,
};

const uint8_t W[] PROGMEM = {
  B00010000,
  B00100000,
  B01000000,
  B11111110,
  B01000000,
  B00100000,
  B00010000,
  B00000000,
};

const uint8_t NW[] PROGMEM = {
  B11111000,
  B11000000,
  B10100000,
  B10010000,
  B10001000,
  B00000100,
  B00000010,
  B00000000,
};

const uint8_t* const DIRECTIONS[] = {
  N, NE, E, SE, S, SW, W, NW
};
} // arrows namespace

namespace icons {
const uint8_t SUN[] PROGMEM = {
  B00000000, B00000000,
  B00000010, B01000000,
  B00100010, B01000100,
  B00010011, B11001000,
  B00001100, B00110000,
  B00001000, B00010000,
  B01110000, B00001110,
  B00010000, B00001000,
  B00010000, B00001000,
  B01110000, B00001110,
  B00001000, B00010000,
  B00001100, B00110000,
  B00010011, B11001000,
  B00100010, B01000100,
  B00000010, B01000000,
  B00000000, B00000000,
};
const uint8_t MOON[] PROGMEM = {
  B00000000, B00000000,
  B00000001, B11100000,
  B00000110, B00110000,
  B00001000, B00001000,
  B00010000, B11110000,
  B00010001, B00000000,
  B00100010, B00000000,
  B00100010, B00000000,
  B00100010, B00000000,
  B00100010, B00000000,
  B00010001, B00000000,
  B00010000, B11110000,
  B00001000, B00001000,
  B00000110, B00110000,
  B00000001, B11100000,
  B00000000, B00000000,
};
const uint8_t SUN_CLOUDS[] PROGMEM = {
  B00000000, B01000000,
  B00000100, B01000100,
  B00000010, B00001000,
  B00000000, B11100000,
  B00000001, B00010000,
  B00001101, B00010110,
  B00000001, B00010000,
  B00000011, B11010000,
  B00000100, B00100000,
  B00001000, B00010000,
  B00111000, B00011100,
  B01000100, B00100010,
  B10000000, B00000001,
  B10000000, B00000001,
  B01000000, B00000010,
  B00111111, B11111100,
};
const uint8_t MOON_CLOUDS[] PROGMEM = {
  B00000000, B00111100,
  B00000000, B01001000,
  B00000000, B10010000,
  B00000001, B00100000,
  B00000001, B00100000,
  B00000001, B00100000,
  B00000000, B10010000,
  B00000011, B11001000,
  B00000100, B00111100,
  B00001000, B00010000,
  B00111000, B00011100,
  B01000100, B00100010,
  B10000000, B00000001,
  B10000000, B00000001,
  B01000000, B00000010,
  B00111111, B11111100,
};
const uint8_t CLOUDS[] PROGMEM = {
  B00000000, B00000000,
  B00000000, B00000000,
  B00000011, B10000000,
  B00000100, B01000000,
  B00001000, B00100000,
  B00001000, B00100000,
  B00111000, B00111000,
  B01000100, B01000100,
  B10000000, B00000010,
  B10000000, B00000010,
  B10000000, B00000010,
  B01000000, B00000100,
  B00111111, B11111000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
};
const uint8_t HEAVY_CLOUDS[] PROGMEM = {
  B00000011, B11110000,
  B00000100, B00001000,
  B00001100, B00001100,
  B00010010, B00010010,
  B00100000, B00000001,
  B00100011, B11000001,
  B00100100, B00100001,
  B00001000, B00010010,
  B00001000, B00010000,
  B00111000, B00011100,
  B01000100, B00100010,
  B10000000, B00000001,
  B10000000, B00000001,
  B10000000, B00000001,
  B01000000, B00000010,
  B00111111, B11111100,
};
const uint8_t RAIN[] PROGMEM = {
  B00000011, B11000000,
  B00000100, B00100000,
  B00001000, B00010000,
  B00001000, B00010000,
  B00111000, B00011100,
  B01000100, B00100010,
  B10000000, B00000001,
  B10000000, B00000001,
  B10000000, B00000001,
  B01000000, B00000010,
  B00111111, B11111100,
  B00000000, B00000000,
  B00001001, B00100100,
  B00010010, B01001000,
  B00100100, B10010000,
  B01001001, B00100000,
};
const uint8_t SUN_RAIN[] PROGMEM = {
  B00000000, B01000000,
  B00000100, B01000100,
  B00000010, B00001000,
  B00000000, B11100000,
  B00000001, B00010000,
  B00000011, B11010110,
  B00000100, B00110000,
  B00111000, B00011100,
  B01000100, B00100010,
  B10000000, B00000001,
  B10000000, B00000001,
  B01111111, B11111110,
  B00000000, B00000000,
  B00100100, B10010010,
  B01001001, B00100100,
  B10010010, B01001000,
};
const uint8_t MOON_RAIN[] PROGMEM = {
  B00000000, B00011110,
  B00000000, B00100100,
  B00000000, B01001000,
  B00000000, B01010000,
  B00000000, B01010000,
  B00000011, B11010000,
  B00000100, B00101000,
  B00111000, B00011100,
  B01000100, B00100010,
  B10000000, B00000001,
  B10000000, B00000001,
  B01111111, B11111110,
  B00000000, B00000000,
  B00100100, B10010010,
  B01001001, B00100100,
  B10010010, B01001000,
};
const uint8_t STORM[] PROGMEM = {
  B00000011, B11000000,
  B00000100, B00100000,
  B00001000, B00010000,
  B00001000, B00010000,
  B00111000, B00011100,
  B01000100, B00100010,
  B10000000, B00000001,
  B10000000, B01000001,
  B10000000, B10000001,
  B01000001, B00000010,
  B00110011, B11100100,
  B00000000, B01000000,
  B00000100, B10000000,
  B00000101, B00000000,
  B00000110, B00000000,
  B00000111, B10000000,
};
const uint8_t SNOW[] PROGMEM = {
  B00000011, B11000000,
  B00000100, B00100000,
  B00001000, B00010000,
  B00001000, B00010000,
  B00111000, B00011100,
  B01000100, B00100010,
  B10000000, B00000001,
  B10000000, B00000001,
  B01000000, B00000010,
  B00111111, B11111100,
  B00000000, B00000000,
  B01000001, B00000100,
  B11100011, B10001110,
  B01001001, B00100100,
  B00011100, B01110000,
  B00001000, B00100000,
};
const uint8_t MIST[] PROGMEM = {
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00011100, B01110000,
  B11100011, B10001110,
  B00000000, B00000000,
  B00011100, B01110000,
  B11100011, B10001110,
  B00000000, B00000000,
  B00011100, B01110000,
  B11100011, B10001110,
  B00000000, B00000000,
  B00011100, B01110000,
  B11100011, B10001110,
  B00000000, B00000000,
  B00000000, B00000000,
};
} // namespace icons
} // namespace symbols

class WeatherScroller : public HorizontalScroller {
  public:
    void setWeather(const Weather& weather) {
      this->weather = weather;
    }
  protected:
    int16_t render(Display& display, const String& text, const uint8_t textSize = 1) {
      display.setTextSize(textSize);
      display.print(text);
      return text.length() * textSize * CHAR_WIDTH;
    }

    int16_t render(Display& display, const char character, const uint8_t textSize = 1) {
      display.setTextSize(textSize);
      display.print(character);
      return textSize * CHAR_WIDTH;
    }

    int16_t render(Display& display, const float value, const uint8_t textSize = 1) {
      String text(value, 0);
      text.trim();
      return render(display, text, textSize);
    }

    template <typename T>
    int16_t render(Display& display, const T value, const uint8_t textSize = 1) {
      String text(value);
      return render(display, text, textSize);
    }

    int16_t renderWeatherIcon(Display& display, const uint8_t icon[], int16_t x, int16_t y) {
      display.drawBitmap(x, y, icon, 16, 16, WHITE);
      return 16;
    }

    int16_t renderWeatherIcon(Display& display, const String& name, int16_t x, int16_t y) {
      if (String("01d") == name)
        return renderWeatherIcon(display, symbols::icons::SUN, x, y) + 0;
      if (String("01n") == name)
        return renderWeatherIcon(display, symbols::icons::MOON, x, y) + 0;
      if (String("02d") == name)
        return renderWeatherIcon(display, symbols::icons::SUN_CLOUDS, x, y) + 1;
      if (String("02n") == name)
        return renderWeatherIcon(display, symbols::icons::MOON_CLOUDS, x, y) + 1;
      if (String("03d") == name)
        return renderWeatherIcon(display, symbols::icons::CLOUDS, x, y) + 0;
      if (String("04d") == name)
        return renderWeatherIcon(display, symbols::icons::HEAVY_CLOUDS, x, y) + 1;
      if (String("09d") == name)
        return renderWeatherIcon(display, symbols::icons::RAIN, x, y) + 1;
      if (String("10d") == name)
        return renderWeatherIcon(display, symbols::icons::SUN_RAIN, x, y) + 1;
      if (String("10n") == name)
        return renderWeatherIcon(display, symbols::icons::MOON_RAIN, x, y) + 1;
      if (String("11d") == name)
        return renderWeatherIcon(display, symbols::icons::STORM, x, y) + 1;
      if (String("13d") == name)
        return renderWeatherIcon(display, symbols::icons::SNOW, x, y) + 1;
      if (String("50d") == name)
        return renderWeatherIcon(display, symbols::icons::MIST, x, y) + 0;
      return 0;
    }

    int16_t render(Display& display, const int16_t x, const int16_t y) {
      display.setCursor(x, y);
      int16_t length = 0;

      static const uint8_t BIG = 2;
      static const int16_t SPACE = 6;

      { // render icons
        for (uint8_t i = 0; i < weather.getIconsCount(); ++i) {
          int16_t iconLength = renderWeatherIcon(display, weather.getIcon(i), x + length, y);
          if (!iconLength) {
            Serial.print("unknown icon ");
            Serial.println(weather.getIcon(i));
          }
          length += iconLength;
        }
      }
      { // render space
        length += SPACE;
        display.setCursor(x + length, y);
      }

      { // render temperature
        length += render(display, weather.getTemperature(), BIG);
        length += render(display, 'C');
      }
      { // render space
        length += SPACE;
        display.setCursor(x + length, y);
      }
      { // render humidity
        length += render(display, weather.getHumidity(), BIG);
        length += render(display, '%');
      }
      { // render space
        length += SPACE;
        display.setCursor(x + length, y);
      }
      { // render pressure
        length += render(display, weather.getPressure());
        {
          String text = "hPa";
          display.setCursor(x + length - text.length() * CHAR_WIDTH, y + 8);
          display.setTextSize(1);
          display.print(text);
        }
      }
      { // render space
        length += SPACE;
        display.setCursor(x + length, y);
      }
      { // render wind
        String windSpeed(weather.getWindSpeed(), 0);
        windSpeed.trim();
        static const String UNIT("km/h");

        const int16_t upper = 8 /*direction icon*/ + windSpeed.length() * CHAR_WIDTH;
        const int16_t lower = UNIT.length() * CHAR_WIDTH;

        if (lower > upper) {
          {
            display.setCursor(x + length, y + 8);
            length += render(display, UNIT);
          }
          { // render wind direction
            static const int16_t SIZE = 8;
            display.drawBitmap(x + length - windSpeed.length() * CHAR_WIDTH - SIZE, y, symbols::arrows::DIRECTIONS[windIconIndex(weather.getWindDirection())], SIZE, SIZE, WHITE);
          }
          { // render wind speed
            display.setCursor(x + length - windSpeed.length() * CHAR_WIDTH, y);
            render(display, windSpeed);
          }
        } else {
          { // render wind direction
            display.drawBitmap(x + length, y, symbols::arrows::DIRECTIONS[windIconIndex(weather.getWindDirection())], 8, 8, WHITE);
            length += 8;
          }
          { // render wind speed
            display.setCursor(x + length, y);
            length += render(display, windSpeed);
          }
          {
            display.setCursor(x + length - UNIT.length() * CHAR_WIDTH, y + 8);
            render(display, UNIT);
          }
        }
      }

      return length;
    }

  private:
    const static uint8_t CHAR_WIDTH = 6;

    uint16_t windIconIndex(int windDeg) {
      return ((windDeg + 22) / 45) % 8;
    }

    Weather weather;
};

class WeatherPresenter {
  public:
    void setup(Display& display, uint8_t y) {
      scroller.setup(y, display.width());
    }

    void show(Display& display, WeatherProvider& weatherProvider) {
      scroller.setWeather(weatherProvider.getWeather());
      scroller.show(display);
    }

  private:
    WeatherScroller scroller;
};

