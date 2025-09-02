const int buzzerPin = 16;
const int freq = 5000;
const int resolution = 8;

void setup() {
  ledcAttach(buzzerPin, freq, resolution);
}

void loop() {
    ledcWriteNote(buzzerPin, NOTE_E, 5);
    delay(100);
    ledcWriteNote(buzzerPin, NOTE_D, 5);   
    delay(100);
    ledcWriteNote(buzzerPin, NOTE_Fs, 4);
    delay(300);
    ledcWriteNote(buzzerPin, NOTE_Gs, 4);   
    delay(300);
    ledcWriteNote(buzzerPin, NOTE_Cs, 5);
    delay(100);
    ledcWriteNote(buzzerPin, NOTE_B, 4);   
    delay(100);
    ledcWriteNote(buzzerPin, NOTE_D, 4);
    delay(300);
    ledcWriteNote(buzzerPin, NOTE_E, 4);   
    delay(300);
    ledcWriteNote(buzzerPin, NOTE_B, 4);
    delay(100);
    ledcWriteNote(buzzerPin, NOTE_A, 4);   
    delay(100);
    ledcWriteNote(buzzerPin, NOTE_Cs, 4);
    delay(300);
    ledcWriteNote(buzzerPin, NOTE_E, 4);   
    delay(300);
    ledcWriteNote(buzzerPin, NOTE_A, 4);   
    delay(800);
}
