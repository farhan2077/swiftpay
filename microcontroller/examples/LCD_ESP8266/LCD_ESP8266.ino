#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(115200);

  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.home(); // (row = 0, col = 0) > index
}

void loop()
{
  displayMessage("Hello LCD!");
}

void displayMessage(String text)
{
  lcd.clear();
  // lcd.setCursor(2, 0); // (row, col) > index
  lcd.print(text);
}