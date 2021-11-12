#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
Servo dragonBall;

const int diffuseSensor = 4;
int sensorState = 0;

// Masukkan maklumat berikut sesuai network anda.
const char* ssid = "iioott";
const char* password = "classiot123";
const char* mqtt_server = "192.168.0.5";  // alamat IP bagi Raspberry Pi4

// Menamakan topik, pastikan guna nama sendiri
#define sub "group4/servo"

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {
  delay(10);
  // memulakan sambungan ke WiFi
  Serial.println();
  Serial.print("Sambungkan ke ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA); //Station mode sama macam phone
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi bersambung");
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mesej sampai [");
  Serial.print(topic);
  Serial.print("] ");

  if (strstr(topic, sub))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Hidupkan LED jika angka 1 diterima
    if ((char)payload[0] == '1') {
      dragonBall.write(90);
      Serial.println("Gate Open");
    } else {
      dragonBall.write(0);
      Serial.println("Gate Close");
    }
  }else
  {
    Serial.println("unsubscribed topic");
  }
}

void reconnect() {
  // Ulang sehingga ada sambungan ke mqtt
  while (!client.connected()) {
    Serial.print("Sambungkan ke MQTT...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("bersambung");
      // arahan untuk subscribe
      client.subscribe(sub);
    } else {
      Serial.print("gagal, rc=");
      Serial.print(client.state());
      Serial.println(" cuba lagi selepas 5 saat");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  Serial.begin(115200);
  dragonBall.attach(23,500,2500);
  pinMode(diffuseSensor,INPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  sensorState = digitalRead(diffuseSensor);
  if (sensorState == LOW){
    dragonBall.write(0);
    Serial.println("Gate Open");
    client.publish("group4/status", "Gate Open");
    delay(1000);
  }else{
    dragonBall.write(90);
    Serial.println("Gate Close");
    client.publish("group4/status", "Gate Close");
  }
  delay(50);
}
