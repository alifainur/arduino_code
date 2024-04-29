#include <ESP32Servo.h>
#include <DHT.h>
DHT dht(33, DHT11);
Servo weeekly;

const int diffuseSensor = 13;
int sensorState = 0;

TaskHandle_t Task1;

void loop2( void * parameters ){
  for (;;) {
    delay(1000);
    float humi = dht.readHumidity();
    float temp = dht.readTemperature();
    if (isnan(humi) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    Serial.printf(("          Temperature: %.2f°C \t Humidity: %.2f%% \n"),temp,humi);
  }
}

void setup() {
  weeekly.attach(12,500,2500);
  pinMode(diffuseSensor,INPUT);
  Serial.begin(9600);
  dht.begin();

  xTaskCreatePinnedToCore(loop2, "dht11", 5000, NULL, 1, &Task1, 0);
}

void loop() {
  sensorState = digitalRead(diffuseSensor);
  if (sensorState == LOW){
    weeekly.write(0);
    Serial.println("Gate Open");
    delay(1000);
  }else{
    weeekly.write(180);
    Serial.println("Gate Close");
  }
  delay(50);
}
