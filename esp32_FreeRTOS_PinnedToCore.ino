int count1 = 0; // mulakan variable count1 dengan nilai 0
int count2 = 0; // mulakan variable count2 dengan nilai 0

// task handle diperlukan untuk membolehkan task dihantar pada core 0 atau 1
TaskHandle_t Task1_handle;
TaskHandle_t Task2_handle;

// Task pertama bermula di sini
void task1(void * parameters){
  for(;;){ // berfungsi sama seperti void loop
    Serial.print("Task 1 Count: ");
    Serial.println(count1++); // tambahkan kiraan +1
    vTaskDelay(1000 / portTICK_PERIOD_MS); // delay 1 saat
  }
}

// Task kedua bermula di sini
void task2(void * parameters){
  for(;;){
    Serial.print("Task 2 Count: ");
    Serial.println(count2+=3); // tambahkan kiraan +3
    vTaskDelay(1000 / portTICK_PERIOD_MS); // delay 1 saat
  }
}

void setup() {
  Serial.begin(115200);
// create task then pinned to core(task function, task name, stack size, parameter, priority, task handle, pin task to core)
  xTaskCreatePinnedToCore(task1, "Task 1", 1000, NULL, 1, &Task1_handle, 0);
  xTaskCreatePinnedToCore(task2, "Task 2", 1000, NULL, 1, &Task2_handle, 1);
}

void loop() {
  // put your main code here, to run repeatedly:
}
