#include <Arduino.h>
#include "dht_sensor.h"
#include <WiFiConnector.h>

#define SECONDS 1000

#ifndef WIFI_SSID
  #define WIFI_SSID "esp8266"
  #define WIFI_PASS "8D5Y9MD306L"
#endif

WiFiConnector wifi(WIFI_SSID, WIFI_PASS);
//WifiController mWifi;
DHT mDHT11;
int temperature;
int humidity;
bool initialised = false;

void setupVar() {
  Serial.println("setupVar");
  mDHT11 = DHT();
  WiFi.disconnect(true);
  temperature = -1;
  humidity = -1;
  initialised = true;
}

void init_wifi() {
  wifi.init();
  wifi.on_connected([&](const void* message)
  {
    Serial.print("WIFI CONNECTED WITH IP: ");
    Serial.println(WiFi.localIP());
  });

  wifi.on_connecting([&](const void* message)
  {
    Serial.print("Connecting to ");
    Serial.println(wifi.get("ssid") + ", " + wifi.get("password"));
    delay(200);
  });
}

void setup() {
  Serial.begin(9600);
  delay(5*SECONDS);
  if (!initialised) {
    setupVar();
    init_wifi();
    wifi.connect();
  }
  Serial.println("Main setup");
}

int readDHT11() {
  if (mDHT11.getData() == 0) {
    temperature = mDHT11.getHumidity();
    humidity = mDHT11.getTemperature();
    return 0;
  }
  return -1;
}

void loop() {
  Serial.println("Main loop");
  if (initialised) {
    mDHT11.loop();
    wifi.loop();
    if (readDHT11() == 0) {
      Serial.print("Temperature: ");
      Serial.println(temperature);
      Serial.print("Humidity: ");
      Serial.println(humidity);
    }
  }
  else {
    Serial.println("Setup not initialised");
  }
  delay(10*SECONDS);

}
