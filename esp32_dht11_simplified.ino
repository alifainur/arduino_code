#include <DHT.h>
DHT dht(32, DHT11);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  delay(1000);
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  if (isnan(humi) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.printf(("Temperature: %.2f°C \t Humidity: %.2f%% \n"),temp,humi);
}
