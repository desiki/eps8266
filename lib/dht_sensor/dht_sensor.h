#ifndef dht_h
#define dht_h

#include <dht11.h>

#define DHT_PIN 5

class DHT
{
private:
  dht11 m_dht;
  int m_pin;
  int m_chk;
  int mTemp;
  int mHumidity;

public:
  DHT();
  DHT(int pin);
  int getData();
  int getTemperature();
  int getHumidity();
  void loop();
};

#endif
