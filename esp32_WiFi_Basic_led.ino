#include <WiFi.h>

#define ssid "yourSSID"
#define password "yourPASSWORD"

const int led_WiFi = 2;

void connectToWiFi(){
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  digitalWrite(led_WiFi, HIGH);
  Serial.println("Connected to WiFi");
}

void setup() {
  pinMode(led_WiFi, OUTPUT);
  Serial.begin(9600);
  connectToWiFi();
}

void loop() {}

