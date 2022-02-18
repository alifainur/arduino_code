#include <Tone32.h>
#define buzzer 16
#define channel 0

void setup() {}

void loop() {
  tone(buzzer, NOTE_C4, 500, channel);
  noTone(buzzer, 0);
  delay(1000);
  tone(buzzer, NOTE_B4, 500, channel);
  noTone(buzzer, 0);
  delay(1000);
}
