#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define resetButton 43
#define modeButton 47

byte reseteBasildi=0, modedayim=0, modaBasildi=0, resetCounter=0,
     modeCounter=0, modeBirim=0;

bool tek=1;

LiquidCrystal_I2C lcd(0x27, 20, 4);
byte saat=23, dakika=57, saniye=0;
unsigned long int millisOnceki;

void printTime(int, int, int, byte, byte);

void setup()
{
  pinMode(resetButton, INPUT);
  pinMode(modeButton, INPUT);
    
  lcd.begin();
  lcd.clear();
  lcd.print("Hello there!");

  millisOnceki=millis();
}

void loop()
{
  // millis millioncekniden 1  saniye kucuk oldugu surece bekle
  while  (millis()<millisOnceki + 500)
  {
    if (digitalRead(resetButton))
      reseteBasildi=1;
    else
      reseteBasildi=0;
    if (digitalRead(modeButton))
      modaBasildi=1;
    else
      modaBasildi=0;
  }
  tek=!tek;
  
  millisOnceki = millis();
  if (tek)
  {
    saniye++;
    if(saniye>=60)
    {
      saniye=0;
      dakika++;
      if (dakika>=60)
      {
        dakika=0;
        saat++;
        if (saat >= 24)
          saat=0;        
      }
    } 
  }

  if (reseteBasildi && !modedayim)
  {
    resetCounter++;
    if (modedayim==0 && resetCounter==3)
    {
      modedayim=1;
      resetCounter=0;
    }
  }
  else if (modedayim)
  {
      resetCounter=0;
      if (modaBasildi==1)
        modeBirim = (modeBirim+1)%3;
        
      if (modeBirim==0)
      {
        if (reseteBasildi)
          saniye=0;
      }
      else if (modeBirim==1)
      {
        if (reseteBasildi)
          dakika=(dakika+1)%60;
      }
      else
      {
        if (reseteBasildi)
          saat=(saat+1)%24;
      }
    }

  if (modaBasildi && modedayim)
  {
    modeCounter++;
    if (modeCounter==4)
    {
      reseteBasildi=0;
      modedayim=0;
      resetCounter=0;
      modeCounter=0;
    }
  }
  else
  {
    modeCounter=0;
  }
  
  printTime(saat, dakika, saniye, modedayim, modeBirim);
}

void printTime(int saat, int dakika, int saniye, byte modedayim, byte modeBirim)
{
  lcd.clear();
  lcd.setCursor(0, 0);    
  if (saat<10)
      lcd.print("0");
  lcd.print(saat);
  lcd.print(":");
  if (dakika<10)
      lcd.print("0");
  lcd.print(dakika);
  lcd.print(":");
  if (saniye<10)
    lcd.print("0");
  lcd.print(saniye);
  if (modedayim)
  {
    lcd.setCursor(0, 1);
    lcd.print("In mode.");
    lcd.setCursor(0, 2);
    lcd.print("Mode Birim: ");
    lcd.print(modeBirim);
  }
  
}
  
