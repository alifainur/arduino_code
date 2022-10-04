const int pin = 16;
const int chan = 0;

void setup() {
  ledcAttachPin(pin,chan);
}

void loop() {
  ledcWriteNote(chan, NOTE_C, 4);
  delay(500);
  ledcWrite(chan,0);
  delay(500);
}
