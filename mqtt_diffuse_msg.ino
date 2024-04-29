#include <WiFi.h>
#include <PubSubClient.h>

const int sensorPin = 13;
int sensorState = 0;
const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";
const char* mqtt_server = "broker.hivemq.com";
//const char* mqtt_server = "broker.mqttdashboard.com";
//const char* mqtt_server = "iot.eclipse.org";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];

void setup_wifi() {
   delay(100);
  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  
} //end callback

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if you MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
     //once connected to MQTT broker, subscribe command if any
      client.subscribe("ali/fainur");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
} //end reconnect()

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(sensorPin,INPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  // hantar data setiap 0.5s
  if (now - lastMsg > 500) {
     lastMsg = now;
     sensorState=digitalRead(sensorPin);
     String msg = "Sensor status: ";
     if(sensorState == LOW)
     {
        msg = msg+ "Detected";
       char message[58];
       msg.toCharArray(message,58);
       Serial.println(message);
       //publish sensor data to MQTT broker
      client.publish("ali/fainur/sensor", message);
       }
     else
     {
      msg = msg+ " Not Detected";
       char message[58];
       msg.toCharArray(message,58);
       Serial.println(message);
       //publish sensor data to MQTT broker
      client.publish("ali/fainur/sensor", message);
     }
    }
     
}
