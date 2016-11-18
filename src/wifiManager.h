#ifndef wifi_h
#define wifi_h

#include <ESP8266WiFi.h>
#include <SPI.h>
#include <WiFiClient.h>

class WifiManager
{
private:
  char *mSsid;
  char *mPass;

public:
  WifiManager();
  WifiManager(char* ssid, char* password);
  bool isConnected();
  void loop();
  void connect();
  void reconnect();
};
#endif
