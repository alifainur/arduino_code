const int pin = 26;
const int freq = 5000;
const int resolution = 8;

void setup() {
  ledcAttach(pin, freq, resolution);
}

void loop() {
    ledcWriteNote(pin, NOTE_E, 5);
    delay(800);
    ledcWriteNote(pin, NOTE_D, 5);   
    delay(400);
    ledcWriteNote(pin, NOTE_Fs, 4);
    delay(400);
    ledcWriteNote(pin, NOTE_Gs, 4);   
    delay(800);
    ledcWriteNote(pin, NOTE_Cs, 5);
    delay(800);
    ledcWriteNote(pin, NOTE_B, 4);   
    delay(400);
    ledcWriteNote(pin, NOTE_D, 4);
    delay(400);
    ledcWriteNote(pin, NOTE_E, 4);   
    delay(800);
    ledcWriteNote(pin, NOTE_B, 4);
    delay(800);
    ledcWriteNote(pin, NOTE_A, 4);   
    delay(400);
    ledcWriteNote(pin, NOTE_Cs, 4);
    delay(400);
    ledcWriteNote(pin, NOTE_E, 4);   
    delay(200);
    ledcWriteNote(pin, NOTE_A, 4);   
    delay(800);
}
