#include <Arduino_JSON.h>

int trigPin = 6;
int echoPin = 7;
long duration, cm, inches;
bool active = false;

JSONVar serialOutput;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (Serial.available() > 0) {
    String jsonString = Serial.readStringUntil("\n");
    if (jsonString != '\n') {
      JSONVar serialInput = JSON.parse(jsonString);

      if (JSON.typeof(serialInput) == "undefined") {
        Serial.println("JSON parsing failed!");
      }
      else {
        active = (bool) serialInput["active"];
      }
    }
  }

  if (active) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    cm = (duration/2) / 29.1;
    inches = (duration/2) / 74;

    serialOutput["cm"] = cm;
    serialOutput["inches"] = inches;

    Serial.println(serialOutput);

  }
}