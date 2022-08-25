#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
  lcd.init();
  lcd.backlight();
}

void loop(){
  digitalWrite(2, HIGH);
  lcd.setCursor(0,0);
  lcd.print("LED : ON");
  delay(1000);
  lcd.clear();
  
  digitalWrite(2, LOW);
  lcd.setCursor(0,0);
  lcd.print("LED : OFF");
  delay(1000);
  lcd.clear(); 
}
