#include <ESP32Servo.h>

Servo servo;

int pos = 0;
int servoPin = 12;

void setup()
{
  Serial.begin(115200);
  servo.attach(servoPin);
}

void loop()
{
  Serial.println("loop()");
  for (pos = 0; pos <= 180; pos += 1)
  {
    servo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1)
  {
    servo.write(pos);
    delay(15);
  }
}