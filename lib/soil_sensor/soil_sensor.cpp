#include "soil_sensor.h"

soilSensor::soilSensor()
{
  this->setPins(VCC_PIN, SOIL_PIN);
}

soilSensor::soilSensor(int vcc_pin, int soil_pin)
{
  this->setPins(vcc_pin, soil_pin);
  pinMode(vccPin, OUTPUT);
  pinMode(soilPin,INPUT);
}

void soilSensor::setPins(int vcc_pin, int soil_pin)
{
  vccPin = vcc_pin;
  soilPin = soil_pin;
}

bool soilSensor::readData()
{
  digitalWrite(vccPin, HIGH);
  delay(10000);
  lastReadedValue = analogRead(A0);
  return true; // todo: add checks
}

float soilSensor::readValuePer()
{
  return ((float)readAbsoluteValue()/1024)*100;
}

int soilSensor::readAbsoluteValue()
{
  return lastReadedValue;
}
