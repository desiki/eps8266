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

int temperature = -1;
int humidity = -1;
float soilHumidity = 0.0;

void setup() {
  Serial.begin(9600);
  delay(2*SECONDS);
}

int readDHT11() {
  if (mDHT11.getData() == 0) {
    humidity  = mDHT11.getHumidity();
    temperature = mDHT11.getTemperature();
    return 0;
  }
  return -1;
}

bool readSoilSensor()
{

  return true;
}

void loop() {
  Serial.println("Main loop");
  if (readDHT11() == 0)
  {
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Humidity: ");
    Serial.println(humidity);
  }
  if (readSoilSensor())
  {
    soilHumidity = mSoil.readValuePer();
    Serial.print("Soil moisture is: ");
    Serial.print(soilHumidity);
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
