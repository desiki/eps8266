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
  Serial.println("soilSensor::readData()");
  digitalWrite(vccPin, HIGH);
  pinMode(soilPin,INPUT);
  delay(0.1*1000);
  lastReadedValue = analogRead(soilPin);
  delay(0.1*1000);
  lastReadedValue = constrain(lastReadedValue, 300 , 1023);
  Serial.println("lastReadedValue = " + lastReadedValue);
  digitalWrite(vccPin, LOW);
  Serial.println("soilSensor::readData() finished");
  return true; //TODO: needs some checks
}

float soilSensor::readValuePer()
{
  return ((float)readAbsoluteValue()/1024)*100;
}

int soilSensor::readAbsoluteValue()
{
  return lastReadedValue;
}
