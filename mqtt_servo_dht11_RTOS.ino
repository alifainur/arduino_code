#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
#include <DHT.h>

const char* ssid = "iotclass@unifi";
const char* password = "classiot123";
const char* mqtt_server = "192.168.0.215";
const char* topic_weeekly = "servo/weeekly";

Servo weeekly;

DHT dht(32, DHT11);
char temp[10];
char humi[10];

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
char msg[50];
int value = 0;

TaskHandle_t Task1_handle;

void task1(void* parameters) {
  for (;;) {  // berfungsi sama seperti void loop
    float t = dht.readTemperature();
    dtostrf(t, 4, 2, temp);
    float h = dht.readHumidity();
    dtostrf(h, 4, 2, humi);
    /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/

    Serial.printf(("Suhu: %.2f°C \t Kelembapan: %.2f%% \n"), t, h);

    client.publish("weeekly/dailee/temp", temp);
    client.publish("weeekly/dailee/humi", humi);
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // delay 1 saat
  }
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32alifainur")) {
      Serial.println("connected");
      client.subscribe(topic_weeekly);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String string;
  // Affiche le topic entrant - display incoming Topic
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  // décode le message - decode payload message
  for (int i = 0; i < length; i++) {
    string += ((char)payload[i]);
  }
  // Affiche le message entrant - display incoming message
  Serial.print(string);
  Serial.print(" toInt ");
  // Conversion de la position en entier - convert position as an Integer
  int pos = string.toInt();
  Serial.println(pos);

  // Détermine quel servo doit être bougé - Determines which servo should be moved
  if (strcmp(topic, topic_weeekly) == 0) {
    Serial.print("Move weeekly to ");
    Serial.println(pos);
    weeekly.write(pos);
  }
  delay(15);
}

void setup() {
  Serial.begin(115200);
  weeekly.attach(12, 500, 2500);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  xTaskCreatePinnedToCore(task1, "Task 1", 5000, NULL, 1, &Task1_handle, 0);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(50);
}