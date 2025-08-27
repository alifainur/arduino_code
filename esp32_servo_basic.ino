#include <ESP32Servo.h>
Servo weeekly;  // menamakan servo sebagai 'weeekly'

void setup() 
{
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  weeekly.setPeriodHertz(50);
  weeekly.attach(26, 500, 2500);  // 26=pin, 500=minimum(500us), 2500=maximum(2500us)
  // Pin GPIO PWM yang digalakkan di ESP32 adalah pin 2,4,12-19,21-23,25-27,32-33
}

void loop() 
{
  weeekly.write(0);  // kedudukan servo 0°
  delay(1500);
  weeekly.write(180);  // kedudukan servo 180°
  delay(1500);
}
