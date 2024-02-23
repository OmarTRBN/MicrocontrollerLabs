#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
byte onceki, simdiki, depo[100], depola, counter;
int saat, dakika, saniye;

void setup()
{ 
  lcd.begin();
  lcd.clear();
  Serial.begin(9600);
}

void writeTimeLCD(int saat, int dakika, int saniye)
{
  lcd.setCursor(6, 0);
  if (saat < 10)
    lcd.print("0");
  lcd.print(saat);
  lcd.print(".");
  if (dakika < 10)
    lcd.print("0");
  lcd.print(dakika);
  lcd.print(".");
  if (saniye < 10)
    lcd.print("0");
  lcd.print(saniye);
}

void loop()
{
  if (Serial.available())
  {
    simdiki = Serial.read();
    
    if (depola == 0)
    {
      if (onceki == 'M' && simdiki == 'C')
      {
        counter = 0;
        depola = 1;
      }
      else
      {
        onceki = simdiki;
      }
    }
    else 
    {
      depo[counter] = simdiki;
      counter ++;
      if (counter == 7)
      {
        saat = 3 + 10*(depo[1] - 48) + (depo[2] - 48);
        dakika = 10*(depo[3] - 48) + (depo[4] - 48);
        saniye = 10*(depo[5] - 48) + (depo[6] - 48);
        writeTimeLCD(saat, dakika, saniye);
      }
      else if (counter == 68)
      {
        for (int i=13; i<=38; i++)
        {

        }
        depola = 0;
      }
    }
  }
}
