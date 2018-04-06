
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

#include "HTSensor.h"
#include "Display.h"
#include "LocationProvider.h"
#include "WeatherProvider.h"
#include "Private.h"

Display display;

GLocationProvider locationProvider(GOOGLE_API_KEY);
GAddressProvider addressProvider(GOOGLE_API_KEY);
AddressPresenter addressPresenter;
WeatherProvider weatherProvider(OPEN_WEATHER_API_KEY);
WeatherPresenter weatherPresenter;

HTSensor htSensor;
HTPresenter htPresenter;

void setup() {
  Serial.begin(115200);
  display.init();
  display.clear();

  display.print("connect...");
  display.display();

  auto configModeCallback = [&display](WiFiManager * wifiManager) {
    display.clear();
    display.println("connect to");
    display.print(wifiManager->getConfigPortalSSID());
    display.display();
  };

  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);

  if (!wifiManager.autoConnect()) {
    display.print("failed");
    ESP.reset();
  }

  htSensor.setup();
  htPresenter.setup(13);

  addressProvider.setup(&locationProvider);
  addressPresenter.setup(display, 0);

  weatherProvider.setup(&locationProvider);
  weatherPresenter.setup(display, 32);
}

void loop() {
  display.clear();
  display.setTextWrap(false);

  addressPresenter.show(display, addressProvider);
  display.drawFastHLine(0, 9, display.width(), WHITE);
  htPresenter.show(display, htSensor);
  display.drawFastHLine(0, 30, display.width(), WHITE);
  weatherPresenter.show(display, weatherProvider);

  delay(10);
}

