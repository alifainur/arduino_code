#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "iot";
const char* password = "classiot123";
const char* mqtt_server = "192.168.0.200";

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
    digitalWrite(D0,HIGH);
    delay(500);
    digitalWrite(D0,LOW);
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(D0,LOW);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
   if ((char)payload[0] == '0') {
     digitalWrite(D1, LOW);
     client.publish("mtech/out/level4","Lampu A ON");} 
   if ((char)payload[0] == '1'){
     digitalWrite(D1, HIGH);
     client.publish("mtech/out/level4","Lampu A OFF");}
      
   if ((char)payload[0] == '2'){
     digitalWrite(D2, LOW);
     client.publish("mtech/out/level4","Lampu B ON");}
   if ((char)payload[0] == '3'){
     digitalWrite(D2, HIGH);
     client.publish("mtech/out/level4","Lampu B OFF");}
      
   if ((char)payload[0] == '4'){
     digitalWrite(D3, LOW);
     client.publish("mtech/out/level4","Lampu C ON");}
   if ((char)payload[0] == '5'){
     digitalWrite(D3, HIGH);
     client.publish("mtech/out/level4","Lampu C OFF");}
      
   if ((char)payload[0] == '6'){
     digitalWrite(D5, LOW);
     client.publish("mtech/out/level4","Lampu D ON");}
   if ((char)payload[0] == '7'){
     digitalWrite(D5, HIGH);
     client.publish("mtech/out/level4","Lampu D OFF");}
      
   if ((char)payload[0] == '8'){
     digitalWrite(D6, LOW);
     client.publish("mtech/out/level4","Lampu E ON");}
   if ((char)payload[0] == '9'){
     digitalWrite(D6, HIGH);
     client.publish("mtech/out/level4","Lampu E OFF");}
      
   if ((char)payload[0] == 'A'){
     digitalWrite(D7, LOW);
     client.publish("mtech/out/level4","Lampu F ON");}
   if ((char)payload[0] == 'B'){
     digitalWrite(D7, HIGH);
     client.publish("mtech/out/level4","Lampu F OFF");}
}

void reconnect() {
  // Loop until we're reconnected
    digitalWrite(D4,HIGH);
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      digitalWrite(D4,LOW);
      // Once connected, publish an announcement...
      client.publish("mtech/out/level4", "Connected to NodeMCU");
      // ... and resubscribe
      client.subscribe("mtech/in/level4");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
    digitalWrite(D4,LOW);
    delay(500);
    digitalWrite(D4,HIGH);
    delay(500);
    digitalWrite(D4,LOW);
    delay(500);
    digitalWrite(D4,HIGH);
    delay(500);
    digitalWrite(D4,LOW);
    delay(500);
    digitalWrite(D4,HIGH);
    delay(500);
    digitalWrite(D4,LOW);
    delay(500);
    digitalWrite(D4,HIGH);
    delay(500);
    digitalWrite(D4,LOW);
    delay(500);
    digitalWrite(D4,HIGH);
    delay(500);
    }
  }
}

void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  digitalWrite(D0,HIGH);
  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  digitalWrite(D3,HIGH);
  digitalWrite(D4,HIGH);
  digitalWrite(D5,HIGH);
  digitalWrite(D6,HIGH);
  digitalWrite(D7,HIGH);
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
