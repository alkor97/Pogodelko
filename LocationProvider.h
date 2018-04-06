
#pragma once
#include <RestClient.h>
#include "Display.h"
#include "Scroller.h"
#include "QueryManager.h"
#include <ArduinoJson.h>

struct Location {
  static const uint8_t MAX_DIGITS = 7;

  Location(float latitude = 0.0f / 0.0f, float longitude = 0.0f / 0.0f)
    : latitude(latitude)
    , longitude(longitude)
  {}

  Location& operator=(const Location& other) {
    const_cast<float&>(latitude) = other.latitude;
    const_cast<float&>(longitude) = other.longitude;
    return *this;
  }

  String latitudeString(uint8_t digits = MAX_DIGITS) const {
    return String(latitude, digits);
  }

  String longitudeString(uint8_t digits = MAX_DIGITS) const {
    return String(longitude, digits);
  }

  String toString(uint8_t digits = MAX_DIGITS) const {
    return latitudeString(digits) + String(',') + longitudeString(digits);
  }

  bool operator==(const Location& other) const {
    return latitude == other.latitude && longitude == other.longitude;
  }

  bool operator!=(const Location& location) const {
    return !operator==(location);
  }

  const float latitude;
  const float longitude;
};

class GLocationProvider : public QueryManager {
  public:
    GLocationProvider(const char* apiKey)
      : QueryManager(15 * MINUTE)
      , apiKey(apiKey)
    {}

    Location getLocation() {
      doQuery();
      return location;
    }

  private:
    void doQuery() {
      auto q = [&]() -> bool {
        return queryCoordinates();
      };
      query(q);
    }

    bool queryCoordinates() {
      RestClient client("www.googleapis.com", 443, 1);
      String path = "/geolocation/v1/geolocate?key=";
      path += apiKey;
      String response;
      String body;
      int statusCode = client.post(path.c_str(), body.c_str(), &response);
      if (statusCode == 200) {
        const size_t bufferSize = 2 * JSON_OBJECT_SIZE(2) + 70;
        DynamicJsonBuffer jsonBuffer(bufferSize);
        JsonObject& root = jsonBuffer.parseObject(response);
        if (root.success()) {
          location = Location(root["location"]["lat"], root["location"]["lng"]);

          Serial.print("Coordinates: ");
          Serial.println(location.toString());

          return true;
        } else {
          Serial.print("Unable to parse coordinates from: ");
          Serial.println(response);
        }
      } else {
        Serial.print("Error while querying coords, statusCode = ");
        Serial.println(statusCode);
      }
      return false;
    }

  private:
    const char* apiKey;
    Location location;
};

class GAddressProvider {
  public:
    GAddressProvider(const char* apiKey)
      : apiKey(apiKey)
      , locationProvider(NULL)
    {}

    void setup(GLocationProvider* locationProvider) {
      this->locationProvider = locationProvider;
    }

    String getAddress() {
      queryAddress();
      return address;
    }

  private:
    bool queryAddress() {
      if (!locationProvider) {
        Serial.println("Location provider not set");
        return false;
      }
      const Location location = locationProvider->getLocation();

      if (location == lastLocation) {
        return true;
      }
      lastLocation = location;

      RestClient client("maps.googleapis.com", 443, 1);
      String path = "/maps/api/geocode/json?latlng=";
      path += location.toString();
      path += "&result_type=locality";
      path += "&key=";
      path += apiKey;

      String response;
      int statusCode = client.get(path.c_str(), &response);
      if (statusCode == 200) {
        const size_t bufferSize = JSON_ARRAY_SIZE(1) + 7 * JSON_ARRAY_SIZE(2) + JSON_ARRAY_SIZE(6) + 8 * JSON_OBJECT_SIZE(2) + 6 * JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + 970;
        DynamicJsonBuffer jsonBuffer(bufferSize);
        JsonObject& root = jsonBuffer.parseObject(response);

        if (root.success()) {
          JsonArray& results = root["results"];
          for (const auto& result : results) {
            address = static_cast<const char*>(result["formatted_address"]);
            Serial.print("Address: ");
            Serial.println(address);
            return true;
          }
        }
        Serial.print("Unable to parse address from: ");
        Serial.println(response);
      } else {
        Serial.print("Error while querying address, statusCode = ");
        Serial.println(statusCode);
      }
      address = location.toString();
      return false;
    }

  private:
    const char* apiKey;
    GLocationProvider* locationProvider;
    Location lastLocation;
    String address;
};

class AddressPresenter {
  public:
    void setup(Display& display, uint8_t y) {
      scroller.setup(display, y);
    }

    void show(Display& display, GAddressProvider& addressProvider) {
      display.setTextSize(1);
      scroller.setText(addressProvider.getAddress());
      scroller.show(display);
    }
  private:
    Scroller scroller;
};

