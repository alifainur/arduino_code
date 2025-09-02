const int pin = 16;
const int freq = 5000;
const int resolution = 8;

void setup() {
  ledcAttach(pin, freq, resolution);
}

void loop() {

    ledcWriteTone(pin, 500);
    delay(1000);
    ledcWriteTone(pin, 0);   
    delay(1000);
}


