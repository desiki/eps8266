#include "wifiManager.h"

#define OUT_PIN 4

WifiManager::WifiManager(const char* ssid, const char* password) {
  pinMode(OUT_PIN, OUTPUT);
  WiFi.begin(ssid, password);
  connect();
}

void WifiManager::reconnect() {
    WiFi.reconnect();
}

void WifiManager::connect() {
  Serial.println("WifiManager::connect()");
  Serial.println("connection: ");
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED && counter < 10) {
        delay(1000);
        Serial.print(".");
        counter++;
  }
  Serial.println(WiFi.status());
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connnection stablished");
    digitalWrite(OUT_PIN, LOW);
  }
  else {
    switch (WiFi.status()) {
      case WL_CONNECT_FAILED:
        Serial.println("WL_CONNECT_FAILED status");
        break;
      case WL_CONNECTION_LOST:
        Serial.println("WL_CONNECTION_LOST status");
        break;
      case WL_DISCONNECTED:
        Serial.println("WL_DISCONNECTED status");
        break;
      case WL_IDLE_STATUS:
        Serial.println("WL_IDLE_STATUS status");
        break;
      default:
        Serial.println("Another status");
        break;
    }
    Serial.println("Connectino lost");
    digitalWrite(OUT_PIN, HIGH);
  }
}

void WifiManager::loop() {
  Serial.println("WifiManager::loop()");
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WifiManager::loop() not CONNECTED");
    digitalWrite(OUT_PIN, HIGH);
    connect();
  }
}

WifiManager::WifiManager() {
}

bool WifiManager::isConnected() {
  return WiFi.status();
}
