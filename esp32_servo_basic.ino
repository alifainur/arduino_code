#include <ESP32Servo.h>
Servo weeekly; // buat servo objek dengan nama 'weeekly'

void setup() {
  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	weeekly.setPeriodHertz(50);
  weeekly.attach(26,500,2500); // 26=pin, 500=min(500us), 2500=max(2500us)
  // PWM GPIO pin yang digalakkan di ESP32 termasuk pin 2,4,12-19,21-23,25-27,32-33 
}

void loop() {
  weeekly.write(0); // suruh servo gerak 0°
  delay(1500);
  weeekly.write(180); // suruh servo gerak 180°
  delay(1500);
}
