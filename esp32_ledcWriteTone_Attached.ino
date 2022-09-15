const int pin = 16;
const int chan = 0;

void setup() {}

void loop() {
  ledcAttachPin(pin,chan);
  ledcWriteTone(chan, 300);
  delay(1000);
  ledcDetachPin(pin);
  delay(1000);
}
