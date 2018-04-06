
#pragma once

#include <ArduinoJson.h>
#include "LocationProvider.h"
#include "Display.h"
#include "QueryManager.h"

const float ZERO_KELVIN = 273.15f;
const float METER_PER_SECOND = 3.6f; // in km/s

class WeatherProvider : public QueryManager {
  public:
    WeatherProvider(const char* apiKey, const long requestPeriod = 10 * MINUTE)
      : QueryManager(requestPeriod)
      , apiKey(apiKey)
      , locationProvider(NULL)
    {}

    void setup(GLocationProvider* locationProvider) {
      this->locationProvider = locationProvider;
    }

    String getWeather() {
      if (!locationProvider) {
        Serial.println("Location provider not set");
        return "";
      }

      const Location location = locationProvider->getLocation();
      const bool force = location != lastLocation;
      lastLocation = location;

      auto q = [&]() -> bool {
        return queryWeather(location);
      };

      query(q, force);
      return weather;
    }

  private:
    bool queryWeather(const Location& location) {
      RestClient client("api.openweathermap.org");
      String q = "/data/2.5/weather?APPID=";
      q += apiKey;
      q += "&lat=";
      q += location.latitudeString();
      q += "&lon=";
      q += location.longitudeString();

      String response;
      int statusCode = client.get(q.c_str(), &response);
      if (statusCode == 200) {
        const size_t bufferSize = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2 * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 400;
        DynamicJsonBuffer jsonBuffer(bufferSize);
        JsonObject& root = jsonBuffer.parseObject(response);
        if (root.success()) {
          weather = "";
          for (int i = 0; i < root["weather"].size(); ++i) {
            if (i > 0)
              weather += " * ";
            String w = root["weather"][i]["description"];
            weather += w;
          }

          float temperature = root["main"]["temp"];
          weather += String(" * ");
          weather += static_cast<int>(temperature - ZERO_KELVIN);
          weather += String("C");

          int pressure = root["main"]["pressure"];
          weather += String(" * ");
          weather += pressure;
          weather += String("hPa");

          int humidity = root["main"]["humidity"];
          weather += String(" * ");
          weather += humidity;
          weather += String("%");

          float windSpeed = root["wind"]["speed"];
          int windDeg = root["wind"]["deg"];
          weather += " * ";
          weather += String("wind ");
          weather += windDirection(windDeg);
          weather += String(" ");
          weather += (int) (METER_PER_SECOND * windSpeed);
          weather += String("km/h");

          int clouds = root["clouds"]["all"];
          weather += " * ";
          weather += "clouds ";
          weather += clouds;
          weather += "%";

          Serial.print("Weather: ");
          Serial.println(weather);

          return true;
        } else {
          Serial.print("Unable to parse weather from: ");
          Serial.println(response);
        }
      } else {
        Serial.print("Error while querying weather, statusCode = ");
        Serial.println(statusCode);
      }
      return false;
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

    const char* apiKey;
    GLocationProvider* locationProvider;
    Location lastLocation;
    String weather;
};

class WeatherPresenter {
  public:
    void setup(Display& display, uint8_t y) {
      scroller.setup(display, y);
    }

    void show(Display& display, WeatherProvider& weatherProvider) {
      display.setTextSize(1);
      scroller.setText(weatherProvider.getWeather());
      scroller.show(display);
    }
  private:
    Scroller scroller;
};

