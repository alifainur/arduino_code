int pushButton = 13;
int blueLED = 2;
int redLED = 4;

TaskHandle_t Task1;

void loop2( void * parameter )
{
  for (;;) {
    // write you code for 2nd loop here to run endlessly
    int buttonState =  digitalRead(pushButton);
    buttonState = !buttonState; 
    // my button was connected through INPUT_PULLUP to GND
    // so I had to inverse the buttonState i.e 0 = 1 and 1 = 0
    if(buttonState == 1){
    Serial.print("            Core#");
    Serial.print(xPortGetCoreID());
    Serial.println("  ButtonPressed");
    delay(50);
    }
    digitalWrite(redLED, buttonState);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  // Initialize your task (2nd loop)
  xTaskCreatePinnedToCore(
    loop2,          // name of the task function
    "buttonCheck",  // name of the task
    1000,           // memory assigned for the task
    NULL,           // parameter to pass if any
    1,              // priority of task, starting from 0(Highestpriority) *IMPORTANT*( if set to 1 and there is no activity in your 2nd loop, it will reset the esp32)
    &Task1,         // Reference name of taskHandle variable
    0);             // choose core (0 or 1)
}

void loop() {
  digitalWrite(blueLED, HIGH);
  Serial.println("  LEDON");
  delay(1000);
  digitalWrite(blueLED, LOW);
  Serial.println("  LEDOFF");
  delay(1000);
}
