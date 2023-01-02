#include "NewPing.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TRIGGER_PIN 25
#define ECHO_PIN 26
#define MAX_DISTANCE 400

float distance;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
  Serial.begin(115200);

  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.home();
}

void loop()
{
  Serial.println("---START---");

  Serial.println("Gate opening");
  lcd.setCursor(2, 0);
  lcd.print("Gate opening");
  delay(3000);
  Serial.println("Gate OPEN. Waiting for vehicle to pass...");
  lcd.setCursor(2, 1);
  lcd.print("Gate open, waiting");

  distance = sonar.ping_cm();

  while (distance < 10)
  {
    delay(500);
    distance = sonar.ping_cm();
    Serial.print(".");
  }

  Serial.println("Vehicle has passed. Gate is closing...");
  lcd.setCursor(2, 0);
  lcd.print("Gate closing");
  delay(3000);
  Serial.println("Gate is CLOSED");
  lcd.setCursor(2, 1);
  lcd.print("Gate CLOSED");

  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}

// void displayMessage(String text)
// {
//   lcd.clear();
//   lcd.setCursor(2, 0);
//   lcd.print(text);
// }