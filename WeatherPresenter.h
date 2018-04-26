
#pragma once

#include "WeatherProvider.h"
#include "Icons.h"

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
      if (String("03d") == name || String("03n") == name)
        return renderWeatherIcon(display, symbols::icons::CLOUDS, x, y) + 0;
      if (String("04d") == name || String("04n") == name)
        return renderWeatherIcon(display, symbols::icons::HEAVY_CLOUDS, x, y) + 1;
      if (String("09d") == name || String("09n") == name)
        return renderWeatherIcon(display, symbols::icons::RAIN, x, y) + 1;
      if (String("10d") == name)
        return renderWeatherIcon(display, symbols::icons::SUN_RAIN, x, y) + 1;
      if (String("10n") == name)
        return renderWeatherIcon(display, symbols::icons::MOON_RAIN, x, y) + 1;
      if (String("11d") == name || String("11n") == name)
        return renderWeatherIcon(display, symbols::icons::STORM, x, y) + 1;
      if (String("13d") == name || String("13n") == name)
        return renderWeatherIcon(display, symbols::icons::SNOW, x, y) + 1;
      if (String("50d") == name || String("50n") == name)
        return renderWeatherIcon(display, symbols::icons::MIST, x, y) + 0;
      return 0;
    }

    int16_t render(Display& display, const int16_t x, const int16_t y) {
      display.setCursor(x, y);
      int16_t length = 0;

      static const uint8_t BIG = 2;
      static const int16_t SPACE = 6;
      static const int16_t ARROW_ICON_SIZE = 8;

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
        const int16_t start = x + length;
        length += render(display, weather.getPressure());
        {
          display.drawBitmap(
            start, y + 8,
            symbols::arrows::CHANGES[tendencyIconIndex(weather.getPressureChange())],
            ARROW_ICON_SIZE, ARROW_ICON_SIZE,
            WHITE);
        }
        {
          static const String text = "hPa";
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

        const int16_t upper = ARROW_ICON_SIZE + windSpeed.length() * CHAR_WIDTH;
        const int16_t lower = UNIT.length() * CHAR_WIDTH;

        if (lower > upper) {
          {
            display.setCursor(x + length, y + 8);
            length += render(display, UNIT);
          }
          { // render wind direction
            display.drawBitmap(
              x + length - windSpeed.length() * CHAR_WIDTH - ARROW_ICON_SIZE, y,
              symbols::arrows::DIRECTIONS[windIconIndex(weather.getWindDirection())],
              ARROW_ICON_SIZE, ARROW_ICON_SIZE,
              WHITE);
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

    uint16_t tendencyIconIndex(int tendency) {
      if (tendency < 0)
        return 0; // SE
      else if (tendency > 0)
        return 1; // NE
      else
        return 2; // E
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

