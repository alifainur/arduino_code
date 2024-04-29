#include <WiFi.h>

#define ssid "yourSSID"
#define password "yourPASSWORD"

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
  Serial.begin(9600);
  connectToWiFi();
}

void loop() {}
