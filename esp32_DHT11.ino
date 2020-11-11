#include "DHT.h"
#define pinDHT 13 
DHT dht(pinDHT, DHT11);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  delay(1000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.printf(("Temperature: %i°C \t Humidity: %i%% \n"),t,h); // press Alt + 0176 for ° Symbol
}
