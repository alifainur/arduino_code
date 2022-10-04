int count1 = 0;
int count2 = 0;

TaskHandle_t Task1_handle;

void task1(void * parameters){
  for(;;){
    Serial.printf("Core#%i Task1 Count: %i \n", xPortGetCoreID(), count1++);
    vTaskDelay(1000 / portTICK_PERIOD_MS); // delay 1 saat
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreatePinnedToCore(task1, "Task 1", 5000, NULL, 1, &Task1_handle, 0);
}

void loop() {
  Serial.printf("Core#%i Task2 Count: %i \n", xPortGetCoreID(), count2+=3);
  delay(1000);
}
