const int buzzer = 16;
const int gasSensor = 4;
// Your threshold value
const int sensorThres = 400;
const int chan = 0;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(gasSensor, INPUT);
  Serial.begin(115200);
}

void loop() {
  int analogSensor = analogRead(gasSensor);

  Serial.print("Pin 4: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    ledcAttachPin(buzzer,chan);
    ledcWriteTone(chan, 300);
  }
  else
  {
    ledcDetachPin(buzzer);
  }
  delay(100);
}
