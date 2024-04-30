const int led1 = 18;
const int led2 = 19;

TaskHandle_t Task1_handle;

void task1(void * parameters){
  for(;;){
    Serial.printf("led1 Core#%i \n", xPortGetCoreID());
    digitalWrite(led1, !digitalRead(led1));
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  xTaskCreatePinnedToCore(task1, "Task 1", 5000, NULL, 1, &Task1_handle, 0);
}

void loop() {
  Serial.printf("led2 Core#%i \n", xPortGetCoreID());
  digitalWrite(led2, !digitalRead(led2));
  delay(200);
}
