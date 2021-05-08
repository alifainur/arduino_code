#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "iot";
const char* password = "classiot123";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    //status for connecting to WiFi
    digitalWrite(19,HIGH);
    delay(500);
    digitalWrite(19,LOW);
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(2,LOW);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
   if ((char)payload[0] == '0') {
     digitalWrite(23, LOW);
     client.publish("mtech/out/iot/9","Lampu ON");} 
   if ((char)payload[0] == '1'){
     digitalWrite(23, HIGH);
     client.publish("mtech/out/iot/9","Lampu OFF");}
}

void reconnect() {
  // Loop until we're reconnected
    digitalWrite(2,LOW);
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      digitalWrite(2,HIGH);
      // Once connected, publish an announcement...
      client.publish("mtech/out/iot/9", "Connected to ESP32");
      // ... and resubscribe
      client.subscribe("mtech/in/iot/9");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
    digitalWrite(2,LOW);
    delay(500);
    digitalWrite(2,HIGH);
    delay(500);
    digitalWrite(2,LOW);
    delay(500);
    digitalWrite(2,HIGH);
    delay(500);
    digitalWrite(2,LOW);
    delay(500);
    digitalWrite(2,HIGH);
    delay(500);
    digitalWrite(2,LOW);
    delay(500);
    digitalWrite(2,HIGH);
    delay(500);
    digitalWrite(2,LOW);
    delay(500);
    digitalWrite(2,HIGH);
    delay(500);
    }
  }
}

void setup() {
  pinMode(2, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(23, OUTPUT);

  digitalWrite(2,HIGH);
  digitalWrite(19,HIGH);
  digitalWrite(23,HIGH);

  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
