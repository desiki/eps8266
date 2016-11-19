#include "soil_sensor.h"

soilSensor::soilSensor()
{
  this->setPins(-1,-1);
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

float soilSensor::readValuePer()
{
  return ((float)readAbsoluteValue()/1024)*100;
}

int soilSensor::readAbsoluteValue()
{
  digitalWrite(vccPin, HIGH);
  delay(0.05*1000);
  lastReadedValue = analogRead(soilPin);
  digitalWrite(vccPin, LOW);
  return lastReadedValue;
}
