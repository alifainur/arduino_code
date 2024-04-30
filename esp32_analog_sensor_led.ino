const int analog_ip = 4;
const int led1 = 18;
const int led2 = 19;
int inputValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  inputValue = analogRead(analog_ip);
Serial.println(inputValue);
  if (inputValue >= 0 && inputValue <= 500) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }
  if (inputValue >= 501 && inputValue <= 119) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
  if (inputValue >= 1200 && inputValue <= 1700) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }

  delay(15);
}
