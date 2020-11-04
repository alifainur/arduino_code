#include <ESP32Servo.h>
Servo myservo;  // create servo object
const int touchPin1 = 12;
const int touchPin2 = 13;
const int touchPin3 = 14;

void setup(){
myservo.attach(23,500,2500);  // (pin, min, max)
}

void loop(){
if (touchRead(touchPin1) < 20) {
    myservo.write(0);
}
if (touchRead(touchPin2) < 20) {
    myservo.write(90);
}
if (touchRead(touchPin3) < 20) {
    myservo.write(180);
}
delay(500);
}
