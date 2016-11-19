#ifndef soil_h
#define soil_h

#include <Arduino.h>

#define VCC_PIN 16
#define SOIL_PIN 0

class soilSensor
{
private:
  int lastReadedValue;
  int vccPin;
  int soilPin;
public:
  soilSensor(int vcc_pin, int soil_pin);
  soilSensor();
  void setPins(int vcc_pin, int soil_pin);
  bool readData();
  float readValuePer(); //  Returns the value in percentage
  int readAbsoluteValue(); // Returns the complete value

};
#endif
