#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

const int led1 = 23;
const int led2 = 19;
const int pushButton = 18;
int buttonState = 0;

void TaskBlink( void *pvParameters);
void TaskDigitalRead( void *pvParameters);

void setup() {
  
  xTaskCreatePinnedToCore(
  TaskBlink
  , "Blink LED"
  , 1024
  , NULL
  , 2
  , NULL
  , ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
  TaskDigitalRead
  , "Read Button" 
  , 1024
  , NULL
  , 1
  , NULL 
  , ARDUINO_RUNNING_CORE);  
}

void loop() {
// Kasi Kosong Saja 
}

void TaskBlink (void *pvParameters)
{
  (void) pvParameters;
  pinMode(led1, OUTPUT);

  for (;;)
  {
    digitalWrite(led1, HIGH);
    vTaskDelay(3000);
    digitalWrite(led1, LOW);
    vTaskDelay(3000);
  }
}

void TaskDigitalRead(void *pvParameters)
{
  (void) pvParameters;
  pinMode(led2,OUTPUT);
  pinMode(pushButton,INPUT);

  for (;;)
  {
    buttonState = digitalRead(pushButton);
    if (buttonState == HIGH){
    digitalWrite(led2, HIGH);
    }else{
    digitalWrite(led2,LOW);
    }
  }
}
