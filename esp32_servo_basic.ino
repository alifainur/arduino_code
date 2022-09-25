#include <ESP32Servo.h>
Servo weeekly;

void setup() {
  weeekly.attach(12,500,2500);
}

void loop() {
  weeekly.write(0);
  delay(1000);
  weeekly.write(180);
  delay(1000);
}
