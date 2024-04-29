#include <DHT.h>
DHT dht(33, DHT11); // pin, jenis DHT.

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(1000);
  Serial.printf(("Temperature: %.2f°C \t Humidity: %.2f%%\n"), dht.readTemperature(), dht.readHumidity());
}
