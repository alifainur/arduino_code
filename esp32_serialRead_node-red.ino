#include <DHT.h>
#define DHT11PIN 33 //jgn guna 34,35,36,39

DHT dht(DHT11PIN, DHT11);

char temp[10];
char humi[10];

void setup()
{
  
  Serial.begin(9600);
/* Start the DHT11 Sensor */
  dht.begin();
}

void loop()
{
  float h = dht.readHumidity();
  dtostrf(h, 4, 2, humi);
  float t = dht.readTemperature();
  dtostrf(t, 4, 2, temp);

  Serial.print(temp);
  Serial.print("\n");
  Serial.println(humi);
  delay(1000);
}
