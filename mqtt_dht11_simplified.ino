#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#define ssid "yourSSID"
#define password "yourPASSWORD"
#define mqtt_server "broker.hivemq.com"

DHT dht(33, DHT11);
char temp[10];
char humi[10];

WiFiClient espClient;
PubSubClient client(espClient);

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

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32alifainur")) {
      Serial.println("connected");
    } else {
      Serial.println(" trying again");
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  connectToWiFi();
  client.setServer(mqtt_server, 1883);
  dht.begin();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(1000);
  float t = dht.readTemperature();
  dtostrf(t, 4, 2, temp);
  float h = dht.readHumidity();
  dtostrf(h, 4, 2, humi);
  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/

  Serial.printf(("Suhu: %.2f°C \t Kelembapan: %.2f%% \n"), t, h);

  client.publish("ali/fainur/temp", temp);
  client.publish("ali/fainur/humi", humi);
}
