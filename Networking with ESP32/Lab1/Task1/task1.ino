#include <Wire.h>
#include <String.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C address 0x27, 16 column and 4 rows

String myString;

void setup()
{
  Wire.begin();
  
  lcd.begin();
  lcd.clear();

  lcd.print("Hello, World!");
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0)
  {
    myString = Serial.read(); 
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Received: ");
    lcd.setCursor(10, 0);
    lcd.print(myString);  
  }
}
