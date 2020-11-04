#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

const int led = 23;
const int analog_ip = 4;
int inputVal = 0;

void TaskBlink( void *pvParameters);
void TaskAnalogRead( void *pvParameters);

void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
  TaskBlink
  , "Nyala LED"
  , 1024
  , NULL
  , 2
  , NULL
  , ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
  TaskAnalogRead
  , "Baca analog" 
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
  pinMode(led, OUTPUT);

  for (;;)
  {
    digitalWrite(led, digitalRead(led)^1);
    vTaskDelay(1000);
  }
}

void TaskAnalogRead(void *pvParameters)
{
  (void) pvParameters;

  for (;;)
  {
    int inputVal = analogRead(analog_ip);
    Serial.println(inputVal);
    vTaskDelay(10);
  }
}
