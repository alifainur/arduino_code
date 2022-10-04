#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi(){
  delay(10); // Start connecting to WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    // Status for connecting to WiFi
    digitalWrite(2, !digitalRead(2));
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  // Status connected to WiFi
  digitalWrite(2, HIGH);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length){
  if (String((char*)payload) == "hidup"){   // tukar kepada string
    digitalWrite(18, HIGH); // ON relay 1
  }
  if ((char)payload[0] == '1'){  // guna char
    digitalWrite(18, LOW);  // OFF relay 1
  }
  /*if ((char)payload[0] == '2'){
    digitalWrite(19, HIGH); // ON relay 2
  }
  if ((char)payload[0] == '3'){
    digitalWrite(19, LOW);  // OFF relay 2
  }
  if ((char)payload[0] == '4'){
    digitalWrite(23, HIGH); // ON relay 3
  }
  if ((char)payload[0] == '5'){
    digitalWrite(23, LOW);  // OFF relay 3
  }*/
}

void reconnect(){
  digitalWrite(2,LOW);
  while (!client.connected()){
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())){
      Serial.println("connected");
      digitalWrite(2, HIGH);
      // Once connected, publish an announcement...
      client.publish("mtech/out/iot", "Connected to ESp32");
      //... resubscribe
      client.subscribe("mtech/in/iot");
    }else{
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 seconds");
      digitalWrite(2, !digitalRead(2));
      delay(1000);
    }
  }
}

void setup() {
Serial.begin(115200);
pinMode(2, OUTPUT);
pinMode(18,OUTPUT);
pinMode(19,OUTPUT);
pinMode(23,OUTPUT);
setup_wifi();
client.setServer(mqtt_server, 1883);
client.setCallback(callback);
}

void loop() {
  if (!client.connected()){
    reconnect();
  }
  client.loop();
}
