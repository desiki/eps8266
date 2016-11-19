#include <Arduino.h>
#include "dht_sensor.h"
#include "soil_sensor.h"
#include "wifiManager.h"

#define SECONDS 1000
#define SOIL_VCC_PIN 16
#define SOIL_PIN 0

#ifndef WIFI_SSID
  #define WIFI_SSID "esp8266"
  #define WIFI_PASS "8D5Y9MD306L"
#endif

DHT mDHT11 = DHT();
WifiManager mWifi = WifiManager(WIFI_SSID, WIFI_PASS);
soilSensor mSoil = soilSensor(SOIL_VCC_PIN, SOIL_PIN);

void setup() {
  Serial.begin(9600);
  delay(2*SECONDS);
}

void loop() {
  Serial.println("Main loop");
  if (mDHT11.getData() == 0)
  {
    Serial.print("Temperature: ");
    Serial.println(mDHT11.getTemperature());
    Serial.print("Humidity: ");
    Serial.println(mDHT11.getHumidity());
  }
  if (mSoil.readData())
  {
    Serial.print("Soil moisture is: ");
    Serial.print(mSoil.readValuePer());
    Serial.println("%");
  }
  if (!mWifi.isConnected())
  {
    Serial.println("Wifi is disconnected");
    mWifi.connect();
  }
  delay(10*SECONDS);
  Serial.println("Go to sleep");
  //ESP.deepSleep(5 * 1000000);
}
