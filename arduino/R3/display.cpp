#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "display.h"

extern LiquidCrystal_I2C lcd;

void ShowTextLine1(const char* text) {
  lcd.setCursor(0, 0);
  lcd.print(text);
}

void ShowTextLine2(const char* text) {
  lcd.setCursor(0, 1);
  lcd.print(text);
}
