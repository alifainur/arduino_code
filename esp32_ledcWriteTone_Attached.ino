const int buzzerPin = 16;
const int freq = 5000;
const int resolution = 8;

void setup() {}

void loop() {
    ledcAttach(buzzerPin, freq, resolution);
    ledcWriteTone(buzzerPin, 500);
    delay(500);
    ledcWriteTone(buzzerPin, 0);   
    delay(500);
}
