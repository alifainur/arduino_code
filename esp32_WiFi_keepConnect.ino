#include <WiFi.h>

#define SSID "iot_class"
#define PASS "classiot123"

void setup() {
  Serial.begin(115200);
  connectToWiFi();

  xTaskCreatePinnedToCore(
    keepWiFiAlive,
    "Keep WiFi Alive",
    5000,
    NULL,
    1,
    NULL,
    CONFIG_ARDUINO_RUNNING_CORE);
}

void loop() {}

void connectToWiFi(){
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(100);
  }
  Serial.println("Connected to WiFi");
}

void keepWiFiAlive(void * parameters){
  for(;;){
    if(WiFi.status() == WL_CONNECTED){
      Serial.println("WiFi still connected");
      vTaskDelay(10000 / portTICK_PERIOD_MS);
      continue;
    }
    connectToWiFi();
  }
}
