int count1 = 0; // mulakan variable count1 dengan nilai 0
int count2 = 0; // mulakan variable count2 dengan nilai 0

// Task pertama bermula di sini
void task1(void * parameters){
  for(;;){
    Serial.print("Task 1 Count: ");
    Serial.println(count1++);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// Task kedua bermula di sini
void task2(void * parameters){
  for(;;){
    Serial.print("Task 2 Count: ");
    Serial.println(count2+=3);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(9600);
// create task(task function, task name, stack size, parameter, priority, task handle, pin task to core)
  xTaskCreate(task1, "Task 1", 1000, NULL, 1, NULL);
  xTaskCreate(task2, "Task 2", 1000, NULL, 1, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}
