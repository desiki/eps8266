#include "dht_sensor.h"

DHT::DHT() {
  DHT(DHT_PIN);
}

DHT::DHT(int pin) {
  m_pin = pin;
}

int DHT::getData() {
  m_chk = m_dht.read(DHT_PIN);
  if (m_chk == 0) {
    mTemp = m_dht.temperature;
    mHumidity = m_dht.humidity;
    return 0;
  }
  return -1;
}

int DHT::getHumidity() {
  if (m_chk == 0) {
    return mHumidity;
  }
  return -100;
}

int DHT::getTemperature() {
  if (m_chk == 0) {
    return mTemp;
  }
  return -100;
}

void DHT::loop(){

}
