#include <WiFiManager.h>

void setup() {
    WiFi.mode(WIFI_STA);
    Serial.begin(115200);
    WiFiManager wm;
    wm.resetSettings();
    bool res = wm.autoConnect("ESP32_Fainur","aaaaaaaa");

    if(!res) {
        Serial.println("Failed to connect");
    } 
    else {  
        Serial.println("connected to WiFi");
    }

}

void loop() {
    // put your main code here, to run repeatedly:   
}
