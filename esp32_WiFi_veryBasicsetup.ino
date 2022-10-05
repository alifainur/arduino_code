#include <WiFi.h>
const char* ssid = "alifainur";
const char* password =  "sudahlupa";
 
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
   Serial.println("Connected to the WiFi network");
 }
 
void loop() {}
