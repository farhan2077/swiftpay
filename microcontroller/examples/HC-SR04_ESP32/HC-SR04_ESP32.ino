#include "NewPing.h"

#define TRIGGER_PIN  2
#define ECHO_PIN  4
#define MAX_DISTANCE 400

long duration;
float distance;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(115200);

}

void loop() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  Serial.print("Distance = ");
  Serial.print(sonar.ping_cm());
  Serial.println(" cm");

  // delay(2000);
  delay(500);

}
