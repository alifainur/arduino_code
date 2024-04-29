const int touchPin = 4; 
const int ledPin = 18;
const int threshold = 40;
int touchValue;

void setup(){
  Serial.begin(9600);
  pinMode (ledPin, OUTPUT);
}

void loop(){
  touchValue = touchRead(touchPin);
  Serial.println(touchValue);
  if(touchValue < threshold){
    digitalWrite(ledPin, LOW);
  }
  else{
    digitalWrite(ledPin, HIGH);
  }
  delay(500);
}
