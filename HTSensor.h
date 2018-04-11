
#pragma once

#include <DHTesp.h>
#include "Display.h"
#include "QueryManager.h"

class HTSensor : public QueryManager {
  public:
    HTSensor() : QueryManager(5 * SECOND) {}

    void setup() {
      dht.setup(D4, DHTesp::DHT22);
    }

    float getTemperature() {
      auto q = [&]() -> bool {
        return queryHT();
      };
      query(q);
      return temperature;
    }

    float getHumidity() {
      auto q = [&]() -> bool {
        return queryHT();
      };
      query(q);
      return humidity;
    }

  private:
    bool queryHT() {
      float lastTemperature = dht.getTemperature();
      if (abs(lastTemperature - temperature) >= 0.1f) {
        Serial.print("Temperature: ");
        Serial.print(lastTemperature, 1);
        Serial.println('C');
      }
      temperature = lastTemperature;

      float lastHumidity = dht.getHumidity();
      if (abs(lastHumidity - humidity) >= 1.0f) {
        Serial.print("Humidity: ");
        Serial.print(lastHumidity, 0);
        Serial.println('%');
      }
      humidity = lastHumidity;
      return true;
    }

    DHTesp dht;
    float temperature;
    float humidity;
};

class HTPresenter {
  public:
    void setup(uint8_t newY) {
      y = newY;
    }

    void show(Display& display, HTSensor& sensor) {
      float lastTemperature = sensor.getTemperature();
      float lastHumidity = sensor.getHumidity();

      const unsigned char degree = (int) lastTemperature;
      const unsigned char subDegree = (int)(10 * lastTemperature) % 10;
      const unsigned char humidity = lastHumidity < 100 ? lastHumidity : 99;

      display.setCursor(0, y);
      display.setTextSize(2);
      display.print(degree);

      display.setCursor(display.getCursorX(), display.getCursorY() + 7);
      display.setTextSize(1);
      display.print(subDegree);

      display.setCursor(display.getCursorX() + 1, display.getCursorY() - 7);
      display.setTextSize(2);
      display.print('C');

      display.setTextSize(1);
      display.setCursor(display.getCursorX() + 4, display.getCursorY());

      display.print(humidity);
      display.print('%');
    }

  private:
    uint8_t y;
};

