#include <SoftwareSerial.h>
#include <LiquidCrystal.h>


const int rs = 12, en = 13, d4 = 7, d5 = 6, d6 = 5, d7 = 4;

static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;

SoftwareSerial ss(RXPin, TXPin);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte onceki, simdiki, depola, counter, saat, dakika, saniye, depo[37];
float enlem, enlemcm, enlemrad, boylamcm, enlemkm, boylamkm;

void setup()
{

  lcd.begin(16, 2);
  Serial.begin(9600);
  ss.begin(GPSBaud);

  if(ss.available())
    onceki = ss.read();
}

void printSaatLCD(int saat, int dakika, int saniye);

void loop()
{
  if(ss.available())
  {
    simdiki = ss.read();
    if (depola == 0)
    {
      if(onceki == 71 && simdiki == 65)
      {
        counter=37;
        depola=1;
      }
      else
        onceki = simdiki;
    }
    else
    {
      depo[37-counter]=simdiki;
      counter--;
      if(counter==0)
      {
        depola = 0;
        saat = 10*(depo[1]-48)+depo[2] -48+3;
        dakika = 10*(depo[3]-48)+depo[4] -48;
        saniye = 10*(depo[5]-48)+depo[6] -48;

        if(saat<10)
          Serial.print("0");
        Serial.print(saat);
        Serial.print(":");
        if(dakika < 10)
          Serial.print("0");
        Serial.print(dakika);
        Serial.print(":");
        if(saniye < 10)
          Serial.print("0");
        Serial.print(saniye);
      
        enlem = float((10*(depo[11]-48)+depo[12]-48)*6000000 +(depo[13]-48)*1000000 +(depo[14]-48)*100000 + (depo[16]-48)*10000 + (depo[17]-48)*1000 + (depo[18]-48)*100 + (depo[19]-48)*10 + depo[20]-48);
        enlemrad = enlem*3.1415/1080000000.0;
        enlemcm = enlem*1.852; // 1.852 = 111/60
        boylamcm = float((100*(depo[24]-48)+10*(depo[25]-48)+depo[26]-48)*6000000 +(depo[27]-48)*1000000 +(depo[28]-48)*100000 + (depo[30]-48)*10000 + (depo[31]-48)*1000 + (depo[32]-48)*100 + (depo[33]-48)*10 + depo[34]-48)*1.852*cos(enlemrad);
        enlemkm = enlemcm/100000; 
        boylamkm = boylamcm/100000;    
      
        Serial.print("  ekvatorden mesafe(cm) : ");
        Serial.print(enlemcm);
        Serial.print(" , Greenwich ten mesafe(cm) : ");
        Serial.println(boylamcm);
      } 
    }
  }
}

void printSaatLCD(int saat, int dakika, int saniye)
{
  lcd.setCursor(0, 0);
  lcd.print(saat);
  lcd.setCursor(1, 0);
  lcd.print(":");
  lcd.setCursor(2, 0);
  lcd.print(dakika);
  lcd.setCursor(4, 0);
  lcd.print(":");

  if(saniye>9)
  {

    lcd.setCursor(5, 0);
    lcd.print(saniye);
  }
  else
  {
    lcd.setCursor(5, 0);
    lcd.print("0");
    lcd.setCursor(6, 0);
    lcd.print(saniye);}
    
    lcd.setCursor(0, 1);
    lcd.print(enlemkm);
    lcd.setCursor(7, 1);
    lcd.print(";;");
    lcd.setCursor(9, 1);
    lcd.print(boylamkm);
   }
}