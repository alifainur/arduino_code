const int pin = 16;
const int channel = 0;

void setup() {
  ledcAttachPin(pin,channel);
}

void loop() {
  ledcWriteTone(channel, 500);
  delay(500);
  ledcWrite(channel,0);
  delay(500);
}

