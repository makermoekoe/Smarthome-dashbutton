#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "XXX";
const char* password = "XXX";
const char* mqtt_server = "192.168.2.120";

const char* mqtt_topic = "/home/dashbuttoncc2/#";
const char* mqtt_topic_state = "/home/dashbuttoncc2/state";
const char* mqtt_client = "dashbuttoncc2";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

const int led = 12;
const int button = 15;

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  pinMode(button, INPUT);
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

  while ((WiFi.status() != WL_CONNECTED)/* || (millis() < 1000)*/) {
    digitalWrite(led, HIGH);
    delay(10);
    digitalWrite(led, LOW);
    delay(100);

    if (millis() > 6000) {
      for (int i = 0; i < 4; i++) {
        digitalWrite(led, HIGH);
        delay(200);
        digitalWrite(led, LOW);
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
      delay(200);
      //programmableswitchevent in homekit
      //0 ist einmal drücken
      //1 ist zweimal drücken
      //2 ist lange drücken
      if (digitalRead(button) == 0) {
        client.publish(mqtt_topic_state, "0");
        for (int i = 0; i < 5; i++) {
          digitalWrite(led, HIGH);
          delay(30);
          digitalWrite(led, LOW);
          delay(20);
        }
      }
      else {
        client.publish(mqtt_topic_state, "1");
        for (int i = 0; i < 10; i++) {
          digitalWrite(led, HIGH);
          delay(30);
          digitalWrite(led, LOW);
          delay(20);
        }
      }


      delay(200);
      ESP.deepSleep(0);
      delay(200);
    }
  }
}
