const int ledPin = 18;
int ledState = 0;

const int buttonPin = 26;
int buttonNew;
int buttonOld = 1;

void setup() {
  pinMode(ledPin,OUTPUT);
  pinMode(buttonPin,INPUT);
}

void loop() {
  buttonNew=digitalRead(buttonPin);
  if(buttonOld==0 && buttonNew==1){
if(ledState==0){
digitalWrite(ledPin,HIGH);
ledState=1;
}    
else{
  digitalWrite(ledPin,LOW);
  ledState=0;
}
}
buttonOld=buttonNew;
delay(100);
}
