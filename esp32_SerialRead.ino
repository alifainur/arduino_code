const int relay1 = 21;
const int relay2 = 22;

void setup() {
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int incomingByte = Serial.parseInt();
  if (incomingByte == 0){
    digitalWrite(relay1, HIGH);
  }
  if (incomingByte == 1){ // led ON
    digitalWrite(relay1, LOW);
  }  
  if (incomingByte == 2){
    digitalWrite(relay2, HIGH);
  }  
  if (incomingByte == 3){ // led ON
    digitalWrite(relay2, LOW);
  }        
  }
}
