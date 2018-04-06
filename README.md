# Pogodełko

Simple weather presenter using Wemos with DHT22 humidity/temperature sensor and OLED shield.

Following aspects of weather conditions are presented in OLED screen:
- temperature (from DHT22 sensor)
- humidity (from DHT sensor)
- local address in form of city name and country name (current location in terms of geo-coordinates and address is provided by Google services)
- current weather outside for current location (provided by OpenWeather)

In order to provide external information (geo-coordinates, address, weather) Wemos needs to be connected to WiFi network.
