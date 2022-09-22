#include <ESP32Servo.h>
Servo weeekly;

const int diffuseSensor = 13;
int sensorState = 0;

void setup() {
  weeekly.attach(12,500,2500);
  pinMode(diffuseSensor,INPUT);
  Serial.begin(115200);
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
