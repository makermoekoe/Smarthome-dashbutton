#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "XXXXX";
const char* password = "XXXXX";
const char* mqtt_server = "XXXXX";

const char* mqtt_topic = "/home/dashbutton2/#";
const char* mqtt_topic_state = "/home/dashbutton2/state";
const char* mqtt_client = "dashbutton2";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

boolean send = false;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    setup_wifi();
  }

  if (!client.connected()) {
    reconnect();
  }

  //client.loop(); //never reaching this
}



void setup_wifi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    if (millis() > 6000) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(BUILTIN_LED, LOW);
        delay(100);
        digitalWrite(BUILTIN_LED, HIGH);
        delay(50);
      }
      ESP.deepSleep(0);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect(mqtt_client)) {
      client.subscribe(mqtt_topic_state);
      delay(300);
      //programmableswitchevent in homekit
      //0 ist einmal drücken
      //1 ist zweimal drücken
      //2 ist lange drücken
      client.publish(mqtt_topic_state, "1");

      send = true;
      for (int i = 0; i < 5; i++) {
        digitalWrite(BUILTIN_LED, LOW);
        delay(30);
        digitalWrite(BUILTIN_LED, HIGH);
        delay(20);
      }
      ESP.deepSleep(0);
    }
  }
}
