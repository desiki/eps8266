#include "wifiManager.h"

#define OUT_PIN 4

WifiManager::WifiManager(){

}

WifiManager::WifiManager(char* ssid, char* password) {
  //WiFi.disconnect(true);
  mSsid = ssid;
  mPass = password;
  pinMode(OUT_PIN, OUTPUT);
}

void WifiManager::connect() {
  int status = WiFi.begin(mSsid, mPass);
  delay(5000);
  if (status == WL_CONNECTED) {
    Serial.print("Connected!! :D ");
    digitalWrite(OUT_PIN, HIGH);
  }

}

void WifiManager::loop() {
  Serial.println("WifiManager::loop()");
}

bool WifiManager::isConnected() {
  if (WL_CONNECTED == WiFi.status()) {
    digitalWrite(OUT_PIN, HIGH);
    return true;
  }
  return false;
}
