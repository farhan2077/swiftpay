#include <ESP32Servo.h>

Servo servo;

int servoPos = 0;
int servoPin = 12;

void setup()
{
  Serial.begin(115200);
  servo.attach(servoPin);
}

void loop()
{
  Serial.println("loop()");
  for (servoPos = 0; servoPos <= 180; servoPos += 1)
  {
    servo.write(servoPos);
    delay(15);
  }
  for (servoPos = 180; servoPos >= 0; servoPos -= 1)
  {
    servo.write(servoPos);
    delay(15);
  }
}