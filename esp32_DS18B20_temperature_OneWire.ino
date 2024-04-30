#include <OneWire.h>
#include <DallasTemperature.h>
const int tempSensor = 27;  //GPIO used for sensor
OneWire oneWire(tempSensor); //Set Communication
DallasTemperature sensors(&oneWire); //Pass OneWire to Dallas

void setup() {
  Serial.begin(115200);
  sensors.begin();
}

void loop() {
  sensors.requestTemperatures(); 
  float tempCelsius = sensors.getTempCByIndex(0);
  float tempFahrenheit = sensors.getTempFByIndex(0);
  Serial.print(tempCelsius);
  Serial.print("ºC    "); //Alt + 0176
  Serial.print(tempFahrenheit);
  Serial.println("ºF"); //Alt + 0176
  delay(2000);
}
