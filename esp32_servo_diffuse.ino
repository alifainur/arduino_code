#include <ESP32Servo.h>
Servo weeekly; // menamakan servo objek dengan nama 'weeekly'

const int diffuseSensor = 13; // variable const = read only
int sensorState = 0;

void setup() {
  weeekly.attach(12,500,2500); //12=pin, 500=min, 2500=max
  pinMode(diffuseSensor,INPUT);
  Serial.begin(115200);
}
void loop() {
  sensorState = digitalRead(diffuseSensor); // bacaan dari diffuseSensor dimasukkan ke sensorState
  
  if (sensorState == LOW){ // buat perbandingan jika sama dengan LOW
    weeekly.write(0); // suruh servo gerak 0°
    Serial.println("Gate Open");
    delay(200);
  }else{
    weeekly.write(180); // suruh servo gerak 180°
    Serial.println("Gate Close");
    delay(200);
  }
  delay(50);
}
