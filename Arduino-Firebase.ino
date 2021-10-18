#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>


#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

FirebaseData fbdo;
FirebaseJson json;
FirebaseJson json2;
QueryFilter query;
bool iterar = true;

const int trigPin = D5;
const int echoPin = D6;
const int trigPin2 = D7;
const int echoPin2 = D8;

long duration;
long duration2;
int distance;
int distance2;
bool parked = false;
bool parked2 = false;
float number;
float number2;
int n = 0;

void setup() {
  Serial.begin(115200);
  delay(10);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
delay(100);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(fbdo, 1000 * 60);
  Firebase.setwriteSizeLimit(fbdo, "medium");
delay(100);
  pinMode(trigPin, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(echoPin2, INPUT);
  //json.set("/PARK", 1);
  Firebase.updateNode(fbdo, "/fass", json);
  Firebase.updateNode(fbdo, "/fens", json2);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  if (distance <= 30) {
    parked = true;
  }
  else
    {parked = false;}
    
  if (parked) {
    Serial.println("1 PARKED!");
    json.set("A10", parked);
    Firebase.updateNode(fbdo, "/fass", json);
  }
  else {
    Serial.print("1 Distance: ");
    Serial.println(distance);
    json.set("A10", parked);
    Firebase.updateNode(fbdo, "/fass", json);
  }
  delay(1000);

  //json.set("number", distance);
  //Firebase.updateNode(fbdo, "/fass", json);

  
  
  /*if (Firebase.getJSON(fbdo, "fass", query)) {
    FirebaseJson &json = fbdo.jsonObject();
    String jsonStr;
    json.toString(jsonStr, true);
    size_t len = json.iteratorBegin();
    String key, value = "";
    int type = 0;

    for (size_t i = 0; i < len; i++) {
      json.iteratorGet(i, type, key, value);
      if (key == "number") {
        number = value.toFloat();
      }
    }
  }
  json.iteratorEnd();
  */
  delay(1000);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  if (distance2 <= 30) {
    parked2 = true;
  }
  else
    parked2 = false;
   
  if (parked2) {
    Serial.println("2 PARKED!");
    json2.set("E10", parked2);
    Firebase.updateNode(fbdo, "/fens", json2);
  }
  else {
    Serial.print("2 Distance: ");
    Serial.println(distance2);
    json2.set("E10", parked2);
    Firebase.updateNode(fbdo, "/fens", json2);
  }
 

  //json.set("number", distance2);
  //Firebase.updateNode(fbdo, "/fens", json);

 
  
  /*if (Firebase.getJSON(fbdo, "fens", query)) {
    FirebaseJson &json = fbdo.jsonObject();
    String jsonStr;
    json.toString(jsonStr, true);
    size_t len = json.iteratorBegin();
    String key, value = "";
    int type = 0;

    for (size_t i = 0; i < len; i++) {
      json.iteratorGet(i, type, key, value);
      if (key == "number") {
        number2 = value.toFloat();
      }
    }
  }
  json.iteratorEnd();
  */
  delay(1000);

}
