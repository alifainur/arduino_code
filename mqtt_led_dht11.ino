#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Menamakan pin led atau relay
#define led1            18
#define led2            19
#define led3            23
#define led4            5

// Menamakan pin 34 sebagai masukan DHT11
#define DHTPIN            34

// Menggunakan sensor DHT11
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Masukkan maklumat berikut sesuai network anda.
const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";
const char* mqtt_server = "broker.hivemq.com";

// Menamakan topik, pastikan guna nama sendiri
#define sub1 "mtech/led1"
#define sub2 "mtech/led2"
#define sub3 "mtech/led3"
#define sub4 "mtech/led4"

char str_hum_data[10];
char str_temp_data[10];

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
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi bersambung");
  Serial.println("Alamat IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mesej sampai [");
  Serial.print(topic);
  Serial.print("] ");

  if (strstr(topic, sub1))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Hidupkan LED jika angka 1 diterima
    if ((char)payload[0] == '1') {
      digitalWrite(led1, HIGH);   // Hidupkan led atau relay
    } else {
      digitalWrite(led1, LOW);    // Matikan led atau relay
    }
  }

  else if ( strstr(topic, sub2))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Hidupkan LED jika angka 1 diterima
    if ((char)payload[0] == '1') {
      digitalWrite(led2, HIGH);   // Hidupkan led atau relay
    } else {
      digitalWrite(led2, LOW);    // Matikan led atau relay
    }
  }
  
  else if ( strstr(topic, sub3))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Hidupkan LED jika angka 1 diterima
    if ((char)payload[0] == '1') {
      digitalWrite(led3, HIGH);   // Hidupkan led atau relay
    } else {
      digitalWrite(led3, LOW);    // Matikan led atau relay
    }
  }
  
  else if ( strstr(topic, sub4))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Hidupkan LED jika angka 1 diterima
    if ((char)payload[0] == '1') {
      digitalWrite(led4, HIGH);   // Hidupkan led atau relay
    } else {
      digitalWrite(led4, LOW);    // Matikan led atau relay
    }
  }

  else
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
      client.subscribe(sub1);
      client.subscribe(sub2);
      client.subscribe(sub3);
      client.subscribe(sub4);
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
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    float hum_data = dht.readHumidity();
    /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
    dtostrf(hum_data, 4, 2, str_hum_data);
    float temp_data = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
    dtostrf(temp_data, 4, 2, str_temp_data);
    lastMsg = now;
    Serial.println(" ");
    Serial.println("Publish message: ");
    Serial.print("Temperature - "); Serial.print(str_temp_data);
    client.publish("mtech/temp", str_temp_data);
    Serial.print(" ");
    Serial.print("Humidity - "); Serial.println(str_hum_data);
    client.publish("mtech/hum", str_hum_data);
  }
}
