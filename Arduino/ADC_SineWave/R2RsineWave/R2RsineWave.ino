// 8 bit R-2R ladder is for pins 24 - 26 - 28 - ... - 38

#define omega 0.001570795  // 2*pi*f = 2*3.14159 * 0.25

byte i;
int sayi;
int D[8];

void setup()
{
  for (i=24; i<=38;  i+=2)
  {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
}

void loop()
{
  sayi=int(127.5*(sin(omega * float(millis())) + 1.0));
//  Serial.println(sayi);
  
  D[7] = sayi/128;
  sayi-=D[7]*128;
  D[6] = sayi/64;
  sayi-=D[6]*64;
  D[5] = sayi/32;
  sayi-=D[5]*32;
  D[4] = sayi/16;
  sayi-=D[4]*16;
  D[3] = sayi/8;
  sayi-=D[3]*8;
  D[2] = sayi/4;
  sayi-=D[2]*4;
  D[1] = sayi/2;
  D[0] = sayi - D[1]*2;

  for (i=24; i<39; i+=2)
  {
      digitalWrite(i, D[7-(i-24)/2]);
  }
  
  delay(1); 
}
