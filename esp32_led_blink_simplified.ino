const int ledPin = 23; // ledPin refers to ESP32 GPIO 23

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin,!digitalRead(ledPin));
  delay(1000);                  // wait for a second
}
