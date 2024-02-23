#define omega 0.001570795 // 2*pi*f = 2 * 3.14159 * 0.25   

int sayi, dir=1;
int D[6];

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  for (int pin = 2; pin <= 9; ++pin)
  {
    pinMode(pin, OUTPUT);
  }
}

void loop()
{
  sayi=int(31.5*(sin(0.001570795 * float(millis())) + 1.0));
  
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

  for (int i=2; i<=7; i++)
  {
      digitalWrite(i, D[i-2]);
  }
  delay(100);
  Serial.println(analogRead(A0)*5/1023);
}
