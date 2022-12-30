#include <Servo.h>

int servoPin = 9;
Servo servo;
int angle = 0;  // servo position in degrees

void setup() {
  servo.attach(servoPin);
  Serial.println("setup() func");
}

void loop() {
  // scan from 0 to 180 degrees
  for (angle = 0; angle < 45; angle++) {
    servo.write(angle);
    delay(15);
  }
  delay(2000);
  // now scan back from 180 to 0 degrees
  for (angle = 45; angle > 0; angle--) {
    servo.write(angle);
    delay(15);
  }
  delay(5000);
  Serial.println("loop() func");
}
