#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// disebabkan WiFi menggunakan AD2, untuk sensor kita gunakan AD1.
/*
WiFi (AD2)
GPIO4, GPIO0, GPIO2, GPIO15, GPIO13, GPIO12, GPIO14, GPIO27, GPIO25 and GPIO26.

ADC1
GPIO36, GPIO37, GPIO38, GPIO39, GPIO32, GPIO33, GPIO34 and GPIO35.
*/
const int analog_ip = 32; 
int sensorValue = 0;
char value[10];

TaskHandle_t Task1_handle;

void task1(void* parameters) {
  for (;;) {  // berfungsi sama seperti void loop
    sensorValue = analogRead(analog_ip);
    dtostrf(sensorValue, 4, 0, value);
    client.publish("esp32/alifainur/water", value);
    Serial.print("Nilai asal: ");
    Serial.println(sensorValue);
    Serial.print("        Nilai selepas convert: ");
    Serial.println(value);
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // delay 1 saat
  }
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected to WiFi");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32_dailee")) {
      Serial.println("connected");
    } else {
      Serial.println(" trying again");
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  client.setServer(mqtt_server, 1883);
  xTaskCreatePinnedToCore(task1, "Water level", 1000, NULL, 1, &Task1_handle, 0);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
