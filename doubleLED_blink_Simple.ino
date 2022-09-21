const int led1 = 19;
const int led2 = 23;

void setup() {
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
}

void loop() {
digitalWrite(led1,!digitalRead(led1));
delay(2000);
digitalWrite(led2,!digitalRead(led2));
delay(200);
}
