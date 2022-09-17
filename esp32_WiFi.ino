#include "WiFi.h"

#define SSID "iot_class"
#define PASS "classiot123"

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

void setup() {
  Serial.begin(115200);
  connectToWiFi();
}

void loop() {}
