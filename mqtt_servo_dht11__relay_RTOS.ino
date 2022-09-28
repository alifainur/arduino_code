#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
#include <DHT.h>

const char* ssid = "iotclass@unifi";
const char* password = "classiot123";
const char* mqtt_server = "broker.hivemq.com";
// List all the topic at mqtt here
const char* topicServo = "servo/weeekly";
const char* topicRelay1 = "alifainur/relay1";
const char* topicRelay2 = "alifainur/relay2";
const char* topicHumi = "alifainur/humidity";
const char* topicTemp = "alifainur/temperature";

const int relay1 = 18;
const int relay2 = 19;
String relay1_Status;
String relay2_Status;

int servoPosition = 0;


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
TaskHandle_t Task2_handle;
TaskHandle_t Task3_handle;
TaskHandle_t Task4_handle;

void task1(void* parameters) {
  for (;;) {  // berfungsi sama seperti void loop
    float t = dht.readTemperature();
    dtostrf(t, 4, 2, temp);
    float h = dht.readHumidity();
    dtostrf(h, 4, 2, humi);
    /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/

    Serial.printf(("Suhu: %.2fC \t Kelembapan: %.2f%% \n"), t, h);

    client.publish(topicTemp, temp);
    client.publish(topicHumi, humi);
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // delay 1 saat
  }
}

void task2(void* parameters) {
  for (;;) {  // berfungsi sama seperti void loop
    weeekly.write(servoPosition);
    //Serial.println(servoPosition);
    vTaskDelay(15 / portTICK_PERIOD_MS);  // delay 1 saat
  }
}

void task3(void* parameters) {
  for (;;) {  // berfungsi sama seperti void loop
    if (relay1_Status == "R1_ON"){
      digitalWrite(relay1, LOW);
      //Serial.println("Relay 1 Close");
    }
    if (relay1_Status == "R1_OFF"){
      digitalWrite(relay1, HIGH);
      //Serial.println("Relay 1 Open");
    }
    vTaskDelay(15 / portTICK_PERIOD_MS);  // delay 1 saat
  }
}

void task4(void* parameters) {
  for (;;) {  // berfungsi sama seperti void loop
    if (relay2_Status == "R2_ON"){
      digitalWrite(relay2, LOW);
      //Serial.println("Relay 2 Close");
    }
    if (relay2_Status == "R2_OFF"){
      digitalWrite(relay2, HIGH);
      //Serial.println("Relay 2 Open");
    }
    vTaskDelay(15 / portTICK_PERIOD_MS);  // delay 1 saat
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
      client.subscribe(topicServo);
      client.subscribe(topicRelay1); 
      client.subscribe(topicRelay2);       
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
// Payload is in byte array, length is the length of the payload.
void callback(char* topic, byte* payload, unsigned int length) {
  String messageTemp;
  // decode payload message
  for (int i = 0; i < length; i++) {
    messageTemp += ((char)payload[i]);
  }
  // Store data to servo
  if (strcmp(topic, topicServo) == 0) {
    servoPosition = messageTemp.toInt(); // convert string to int
  }
  if (strcmp(topic, topicRelay1) == 0) {
    relay1_Status = messageTemp; // transfer data
  }
  if (strcmp(topic, topicRelay2) == 0) {
    relay2_Status = messageTemp; // transfer data
  }
  delay(15);
}

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  Serial.begin(115200);
  weeekly.attach(12, 500, 2500);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  reconnect();
  //Pastikan priority tidak sama jika sama CORE
  xTaskCreatePinnedToCore(task1, "DHT11", 5000, NULL, 2, &Task1_handle, 0);
  xTaskCreatePinnedToCore(task2, "Servo", 5000, NULL, 2, &Task2_handle, 1);
  xTaskCreatePinnedToCore(task3, "Relay 1", 5000, NULL, 1, &Task3_handle, 0);
  xTaskCreatePinnedToCore(task4, "Relay 2", 5000, NULL, 3, &Task3_handle, 1);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  delay(50);
}