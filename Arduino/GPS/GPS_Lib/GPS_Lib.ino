#include <TinyGPSPlus.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

TinyGPSPlus gps;

void setup()
{
  lcd.begin();
  lcd.clear();
  Serial.begin(9600);
}

void loop()
{
  while (Serial.available() > 0)
  {
    if (gps.encode(Serial.read()))
    {
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Lat: ");
      lcd.print(gps.location.lat(), 6);
      
      lcd.setCursor(0, 1);
      lcd.print("Long: ");
      lcd.print(gps.location.lng(), 6);

      lcd.setCursor(0, 3);
      lcd.print("Time: ");
      lcd.print((gps.time.hour() + 3) % 24);
      lcd.print(":");
      lcd.print(gps.time.minute());
      lcd.print(":");
      lcd.print(gps.time.second());      
    }
    else
    {
      lcd.print("No data");
      lcd.clear();
    }
  }
}
