const int buzzerPin = 16;
const int freq = 5000;
const int resolution = 8;

void setup() {
  ledcAttach(buzzerPin, freq, resolution);
}

void loop() {

    ledcWriteTone(buzzerPin, 500);
    delay(500);
    ledcWriteTone(buzzerPin, 0);   
    delay(500);
}


