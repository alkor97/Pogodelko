
#pragma once

#include <ArduinoJson.h>
#include "LocationProvider.h"
#include "Display.h"
#include "QueryManager.h"

namespace {
const float ZERO_KELVIN = 273.15f;
const float METER_PER_SECOND = 3.6f; // in km/s
} // anonymous namespace

class Weather {
  public:
    Weather()
      : descriptionsCount(0)
      , iconsCount(0)
      , temperature(0.0f)
      , humidity(0)
      , pressure(0)
      , pressureChange(0)
      , windSpeed(0.0f)
      , windDirection(0)
      , cloudCoverage(0)
    {}

    void clear() {
      descriptionsCount = 0;
    }

    bool addDescription(const String& description) {
      if (descriptionsCount < 5) {
        descriptions[descriptionsCount++] = description;
        return true;
      }
      return false;
    }

    const String& getDescription(uint8_t index) const {
      return descriptions[index];
    }

    uint8_t getDescriptionsCount() const {
      return descriptionsCount;
    }

    bool addIcon(const String& icon) {
      if (iconsCount < 5) {
        icons[iconsCount++] = icon;
        return true;
      }
      return false;
    }

    const String& getIcon(uint8_t index) const {
      return icons[index];
    }

    uint8_t getIconsCount() const {
      return descriptionsCount;
    }

    // temperature in Celsius degrees
    float getTemperature() const {
      return temperature - ZERO_KELVIN;
    }

    void setTemperature(float v) {
      temperature = v;
    }

    // humidity as a percentage
    uint8_t getHumidity() const {
      return humidity;
    }

    void setHumidity(uint8_t v) {
      humidity = v;
    }

    // pressure in hPa
    uint16_t getPressure() const {
      return pressure;
    }

    void setPressure(uint16_t v) {
      pressure = v;
    }

    int getPressureChange() const {
      return pressureChange;
    }

    void setPressureChange(int v) {
      pressureChange = v;
    }

    // wind speed in km/h
    float getWindSpeed() const {
      return windSpeed * METER_PER_SECOND;
    }

    void setWindSpeed(float v) {
      windSpeed = v;
    }

    // wind direction as azimuth (degrees 0-359)
    uint16_t getWindDirection() const {
      return windDirection;
    }

    void setWindDirection(uint16_t v) {
      windDirection = v;
    }

    // cloud coverage as percentage
    uint8_t getCloudCoverage() const {
      return cloudCoverage;
    }

    void setCloudCoverage(uint8_t v) {
      cloudCoverage = v;
    }

    String toString() const {
      String r = "weather:";
      r += " temp.: " + String(getTemperature(), 0) + "C";
      r += " humd.: " + String(getHumidity()) + "%";
      r += " pres.: " + String(getPressure()) + "hPa," + getTendency(getPressureChange());
      r += " wind: " + String(getWindDirection()) + " (" + toWindDirection(getWindDirection()) + ") " + String(getWindSpeed(), 0) + "km/h";
      r += " clouds: " + String(getCloudCoverage()) + "%";
      r += " desc.:";
      for (int i = 0; i < getDescriptionsCount(); ++i) {
        r += " " + getDescription(i);
      }
      for (int i = 0; i < getIconsCount(); ++i) {
        r += " " + getIcon(i);
      }
      return r;
    }

    String getTendency(int v) const {
      if (v < 0)
        return "falling";
      else if (v > 0)
        return "rising";
      else
        return "stable";
    }

    static String toWindDirection(int windDeg) {
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

  private:
    String descriptions[5];
    uint8_t descriptionsCount;
    String icons[5];
    uint8_t iconsCount;
    float temperature; // in kelvins
    uint8_t humidity; // as percentage
    uint16_t pressure; // in hPa
    int pressureChange;
    float windSpeed; // in m/s
    uint16_t windDirection; // azimuth
    uint8_t cloudCoverage; // as percentage
};

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

    const Weather& getWeather() {
      if (!locationProvider) {
        Serial.println("Location provider not set");
        return weather;
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
          const int prevPressure = weather.getPressure();
          weather.clear();
          for (int i = 0; i < root["weather"].size(); ++i) {
            weather.addDescription(root["weather"][i]["description"]);
            weather.addIcon(root["weather"][i]["icon"]);
          }

          float temperature = root["main"]["temp"];
          weather.setTemperature(temperature);

          int pressure = root["main"]["pressure"];
          weather.setPressure(pressure);
          weather.setPressureChange(pressure - prevPressure);

          int humidity = root["main"]["humidity"];
          weather.setHumidity(humidity);

          float windSpeed = root["wind"]["speed"];
          weather.setWindSpeed(windSpeed);

          int windDeg = root["wind"]["deg"];
          weather.setWindDirection(windDeg);

          int clouds = root["clouds"]["all"];
          weather.setCloudCoverage(clouds);

          Serial.println(weather.toString());

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
    const char* apiKey;
    GLocationProvider* locationProvider;
    Location lastLocation;
    Weather weather;
};

