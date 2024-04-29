#include <WiFi.h>

#define ssid "yourSSID"
#define password "yourPASSWORD"

void connectToWiFi(){
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
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

void setup() {
  Serial.begin(9600);
  connectToWiFi();
  xTaskCreatePinnedToCore(keepWiFiAlive, "Keep WiFi Alive", 5000, NULL, 1, NULL, CONFIG_ARDUINO_RUNNING_CORE);
}

void loop() {}
