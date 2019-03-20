#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "XXX";
const char* password = "XXX";
const char* mqtt_server = "192.168.2.120";

const char* mqtt_topic = "/home/dashbuttonv51/#";
const char* mqtt_topic_state = "/home/dashbuttonv51/state";
const char* mqtt_topic_battery = "/home/dashbuttonv51/battery";
const char* mqtt_topic_batterylevel = "/home/dashbuttonv51/batterylevel";
const char* mqtt_client = "dashbuttonv51";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

const int led = 13;
const int button1 = 14;
const int button2 = 4;
const int button3 = 5;
const int powerhigh = 12;

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  pinMode(powerhigh, OUTPUT);
  digitalWrite(powerhigh, HIGH);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop(); //never reaching this
}



void setup_wifi() {
  WiFi.begin(ssid, password);

  while ((WiFi.status() != WL_CONNECTED)/* || (millis() < 1000)*/) {
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
      delay(100);
      //programmableswitchevent in homekit
      //0 ist einmal drücken
      //1 ist zweimal drücken
      //2 ist lange drücken
      if (digitalRead(button1) == 0) {
        client.publish(mqtt_topic_state, "0");
        for (int i = 0; i < 1; i++) {
          digitalWrite(led, HIGH);
          delay(100);
          digitalWrite(led, LOW);
          delay(50);
        }
      }
      else if (digitalRead(button2) == 0) {
        client.publish(mqtt_topic_state, "1");
        for (int i = 0; i < 3; i++) {
          digitalWrite(led, HIGH);
          delay(100);
          digitalWrite(led, LOW);
          delay(50);
        }
      }
      else if (digitalRead(button3) == 0) {
        client.publish(mqtt_topic_state, "2");
        for (int i = 0; i < 5; i++) {
          digitalWrite(led, HIGH);
          delay(100);
          digitalWrite(led, LOW);
          delay(50);
        }
      }
      delay(300);

      if (calculate_battery_voltage() < 3.5) {
        client.publish(mqtt_topic_battery, "0");
        digitalWrite(led, HIGH);
        delay(1000);
        digitalWrite(led, LOW);
        delay(50);
      }

      client.publish(mqtt_topic_batterylevel, "80");

      delay(100);
      ESP.deepSleep(0);
      delay(200);
    }
  }
}


float calculate_battery_voltage() {
  // U = (R2)/(R1+R2) * U_lipo
  // U = factor * U_lipo

  // 1023 * 22k/104k = 216,403846
  float factor = 216.403846;
  return (analogRead(0) / factor);
}
