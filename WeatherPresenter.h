
#pragma once

#include "WeatherProvider.h"

class WeatherPresenter {
  public:
    void setup(Display& display, uint8_t y) {
      scroller.setup(display, y);
    }

    void show(Display& display, WeatherProvider& weatherProvider) {
      display.setTextSize(1);

      const auto& weather = weatherProvider.getWeather();
      String text = "";
      for (uint8_t i = 0; i < weather.getDescriptionsCount(); ++i) {
        if (i > 0)
          text += " * ";
        text += weather.getDescription(i);
      }

      String t(weather.getTemperature(), 0);
      t.trim();
      text += " * ";
      text += t;
      text += 'C';

      text += " * ";
      text += weather.getHumidity();
      text += '%';

      text += " * ";
      text += weather.getPressure();
      text += "hPa";

      text += " * ";
      text += "wind ";
      text += windDirection(weather.getWindDirection());
      text += ' ';
      text += String(weather.getWindSpeed(), 0);
      text += "km/h";

      text += " * ";
      text += "clouds ";
      text += weather.getCloudCoverage();
      text += '%';

      scroller.setText(text);
      scroller.show(display);
    }
  private:
    String windDirection(int windDeg) {
      if (windDeg < 22)
        return "N";
      if (windDeg < 45 + 22)
        return "NE";
      if (windDeg < 90 + 22)
        return "E";
      if (windDeg < 90 + 45 + 22)
        return "SE";
      if (windDeg < 180 + 22)
        return "S";
      if (windDeg < 180 + 45 + 22)
        return "SW";
      if (windDeg < 270 + 22)
        return "W";
      if (windDeg < 270 + 45 + 22)
        return "NW";
      return "N";
    }
    TextScroller scroller;
};

