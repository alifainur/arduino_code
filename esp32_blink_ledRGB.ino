const int ledPin1 = 18;
const int ledPin2 = 19;
const int ledPin3 = 23;

TaskHandle_t Task1_handle;
TaskHandle_t Task2_handle;

void task1(void * parameters){
  for(;;){
  digitalWrite(ledPin2, !digitalRead(ledPin2));
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void task2(void * parameters){
  for(;;){
  digitalWrite(ledPin3, !digitalRead(ledPin3));
    vTaskDelay(600 / portTICK_PERIOD_MS);
  }
}

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  xTaskCreatePinnedToCore(task1, "Task 1", 1000, NULL, 1, &Task1_handle, 0);
  xTaskCreatePinnedToCore(task2, "Task 2", 1000, NULL, 1, &Task2_handle, 1);
}

void loop() {
  digitalWrite(ledPin1, !digitalRead(ledPin1));
  delay(800);
}