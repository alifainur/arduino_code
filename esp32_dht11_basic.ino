#include <DHT.h>
#define DHT11PIN 33 //jgn guna 34,35,36,39

DHT dht(DHT11PIN, DHT11);

void setup()
{
  Serial.begin(115200);
  dht.begin(); //Start the DHT11 sensor
}

void loop()
{
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("ºC "); // press Alt + 0176 for ° Symbol
  Serial.print("Humidity: ");
  Serial.println(humi);
  delay(1000);
}
