const int potPin = 4;
int inputVal = 0;
const int ledPin = 18;
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup() {
 Serial.begin(9600);
   ledcSetup(ledChannel, freq, resolution);
   ledcAttachPin(ledPin, ledChannel);
 delay(1000);
}

void loop() {
 inputVal = analogRead (potPin);
 Serial.println(inputVal);
 ledcWrite(ledChannel, inputVal/4);
 delay(500);
}
