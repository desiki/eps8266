#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <dht_sensor.h>
#include <soil_sensor.h>
#include <wifiManager.h>

ADC_MODE(ADC_VCC);

#define SECONDS 1000
#define HOUR 3600000
#define SOIL_VCC_PIN 16
#define SOIL_PIN A0

DHT mDHT11 = DHT();
WifiManager mWifi = WifiManager("esp8266", "8D5Y9MD306L");
soilSensor mSoil = soilSensor(SOIL_VCC_PIN, SOIL_PIN);

void setup() {
  Serial.begin(9600);
  delay(2*SECONDS);
}

void sendData(int device, char* field, float value)
{
  HTTPClient http;
  String url = (String("http://192.168.8.10:8080/") + field + "/" + device + "/" + value);
  Serial.println("Url = "+ url);
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode > 0)
  { //Check the returning code
    String payload = http.getString();   //Get the request response payload
    Serial.println(payload);             //Print the response payload
  }
  http.end();
}

void loop()
{
  Serial.println("========================");
  Serial.println("========================");
  Serial.println("Main loop 2.0");
  if (mDHT11.getData() == 0)
  {
    Serial.print("Temperature: ");
    Serial.println(mDHT11.getTemperature());
    sendData(1,"temp", mDHT11.getTemperature());

    Serial.print("Humidity: ");
    Serial.println(mDHT11.getHumidity());
    sendData(1,"humidity", mDHT11.getHumidity());
  }
  else
  {
    Serial.println("mDHT11 not working");
    sendData(1,"dht11",-1.0);
  }
  if (mSoil.readData())
  {
    delay(0.1*1000);
    Serial.print("Soil moisture is: ");
    Serial.print(mSoil.readAbsoluteValue());
    Serial.println("%");
    sendData(1,"moisture",mSoil.readValuePer());
  }
  else
  {
    Serial.println("Soil moisture not working");
    sendData(1,"soilSensor",-1.0);
  }
  if (!mWifi.isConnected())
  {
    Serial.println("Wifi is disconnected");
    mWifi.connect();
  }
  digitalWrite(SOIL_VCC_PIN, LOW);
  delay(10*SECONDS);
  Serial.println("Go to sleep");
}
