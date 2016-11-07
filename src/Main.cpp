#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiConnector.h>
#include <ESP8266HTTPClient.h>

#include "dht11.h"

//#define DHT_TYPE DHT11
#define DHT_PIN 5
#define SECONDS 1000

#ifndef SSID
  #define SSID "esp8266"
  #define PASS "8D5Y9MD306L"
#endif

WiFiConnector wifi(SSID, PASS);

void setupWifi() {
  Serial.println("Setup wifi");
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
    delay(5*SECONDS);
  });
}

void getTempData() {
  dht11 m_dht;
  int chk = m_dht.read(DHT_PIN);
  if (chk == 0) {
    Serial.print("The humidity is: ");
    Serial.println(m_dht.humidity);
    Serial.print("The temperature is ");
    Serial.println(m_dht.temperature);
  }
  else {
    Serial.print("Error reading DHT11: ");
    Serial.println(chk);
  }
}

void setup() {
  Serial.begin(9600);
  delay(2*SECONDS);
  Serial.println("ESP8266 setup");
  wifi.disconnect(true);
  delay(1*SECONDS);
  Serial.println("will be started in 10s...");
  setupWifi();
}

void loop() {
  wifi.loop();
  if (!wifi.connected()) {
    Serial.println("Wifit not connected");
    wifi.connect();
  }
  getTempData();
  delay(5*SECONDS);

}
