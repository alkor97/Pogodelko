# Pogodełko

Simple weather presenter using Wemos with DHT22 humidity/temperature sensor and OLED shield.

Following aspects of weather conditions are presented in OLED screen:
- temperature (from DHT22 sensor)
- humidity (from DHT sensor)
- local address in form of city name and country name (current location in terms of geo-coordinates and address is provided by Google services)
- current weather outside for current location (provided by OpenWeather)

In order to provide external information (geo-coordinates, address, weather) Wemos needs to be connected to WiFi network.

In order to access Google services and OpenWeather service one needs to register there for API keys and provide respective values in {{.cpp}} file in project.

This project uses following external dependencies:
- Adafruit GFX Library (installed from Library Manager of Arduino IDE)
- Adafruit SSD1306 Wemos Mini OLED (installed from Library Manager of Arduino IDE)
- ArduinoJson (installed from Library Manager of Arduino IDE)
- DHT sensor library for ESPx (installed from Library Manager of Arduino IDE)
- esp8266-restclient (installed from https://github.com/dakaz/esp8266-restclient.git)
- WiFiManager (installed from Library Manager of Arduino IDE)
