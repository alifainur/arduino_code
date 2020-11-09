#include <WiFi.h>
#include <PubSubClient.h>
//#include <Wire.h>
#include <DHT.h>
DHT dht(4, DHT11);

WiFiClient espClient;
PubSubClient client(espClient);

const int ledwifi = 18;
const char* ssid = "alifainur"; 
const char* password = "sudahlupa";
const char* mqtt_server = "broker.hivemq.com";

void connectToWiFi(){
 WiFi.begin(ssid, password);
 // Check wifi status
 while (WiFi.status() != WL_CONNECTED){
  Serial.println("reconnect");
  digitalWrite(ledwifi,HIGH);
  delay(500);
  digitalWrite(ledwifi,LOW);
  delay(500);
 }
 Serial.println("Connected");
 digitalWrite(ledwifi,HIGH);
 Serial.println(WiFi.localIP());
}

void connectToMQTT(){
  while (!client.connected()){
   Serial.print("Attempting MQTT connection...");
   String clientId = "ESP32Client-";
   clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())){
      Serial.println("connected to MQTT");
      client.publish("mtech/out/iot/alifainur", "Hello World");
      client.subscribe("mtech/in/iot");
    }else{
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 seconds");
      delay(1000);
    }
  }
}

void setup() {
pinMode(ledwifi,OUTPUT);
Serial.begin(115200);
dht.begin();
connectToWiFi();
client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()){
    connectToMQTT();
  }
  client.loop();

  delay(1000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.printf(("Temperature: %i°C \t Humidity: %i%% \n"),t,h);
  client.publish("alifainur/sensor/temperature", String(t).c_str(),true);
}
