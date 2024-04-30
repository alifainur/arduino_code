#include "DHT.h"
DHT dht(33, DHT11);
#include <LiquidCrystal_I2C.h>
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
  Serial.begin(115200);
  dht.begin();
  lcd.init();                   
  lcd.backlight();
}

void loop()
{
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("ºC   "); // press Alt + 0176 for ° Symbol
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(6, 0);
  lcd.print(temp);
  lcd.setCursor(11, 0);
  lcd.write(0xdf); // symbol degree
  lcd.setCursor(12, 0);
  lcd.print("C");
  
  
  Serial.print("Humidity: ");
  Serial.print(humi);
  Serial.println("%");
  lcd.setCursor(0, 1);
  lcd.print("Humi: ");
  lcd.setCursor(6, 1);
  lcd.print(humi);
  lcd.setCursor(11, 1);
  lcd.print("%");
  delay(1000);
}
