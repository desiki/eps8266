#ifndef wifi_h
#define wifi_h

#include <ESP8266WiFi.h>
#include <SPI.h>
#include <WiFiClient.h>

class WifiManager
{
private:
  bool mConnected;
public:

  WifiManager();
  WifiManager(const char* ssid, const char* password);
  bool isConnected();
  void loop();
  void connect();
  void reconnect();
};
#endif
