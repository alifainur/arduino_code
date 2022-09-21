const int led1 = 19;
const int led2 = 23;

void setup() {
pinMode(led1,OUTPUT);
pinMode(led2,OUTPUT);
}

void loop() {
digitalWrite(led1,HIGH);
delay(2000);
digitalWrite(led1,LOW);
delay(2000);
digitalWrite(led2,HIGH);
delay(200);
digitalWrite(led2,LOW);
delay(200);
}
