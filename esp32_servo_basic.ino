#include <ESP32Servo.h>
Servo weeekly; // buat servo objek dengan nama 'weeekly'

void setup() {
  weeekly.attach(12,500,2500); // 12=pin, 500=min, 2500=max
}

void loop() {
  weeekly.write(0); // suruh servo gerak 0°
  delay(1000);
  weeekly.write(180); // suruh servo gerak 180°
  delay(1000);
}
