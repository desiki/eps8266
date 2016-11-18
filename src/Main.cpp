#include <Arduino.h>
#include "dht_sensor.h"
#include "wifiManager.h"

#define SECONDS 1000

#ifndef WIFI_SSID
  #define WIFI_SSID "esp8266"
  #define WIFI_PASS "8D5Y9MD306L"
#endif

DHT mDHT11;
WifiManager mWifi;
int temperature;
int humidity;

void setupVar() {
  Serial.println("setupVar");
  mWifi = WifiManager(WIFI_SSID, WIFI_PASS);
  mDHT11 = DHT();
  temperature = -1;
  humidity = -1;
}

void setup() {
  Serial.begin(9600);
  delay(5*SECONDS);
  setupVar();
  Serial.println("Main setup");
}

int readDHT11() {
  if (mDHT11.getData() == 0) {
    humidity  = mDHT11.getHumidity();
    temperature = mDHT11.getTemperature();
    return 0;
  }
  return -1;
}

void loop() {
  Serial.println("Main loop");
  if (readDHT11() == 0) {
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Humidity: ");
    Serial.println(humidity);
  }
  if (!mWifi.isConnected()) {
    Serial.println("Wifi is disconnected");
    mWifi.connect();
  }
  mWifi.loop();
}
