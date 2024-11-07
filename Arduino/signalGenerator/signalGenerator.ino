
float omega = 0;
float sineValue=0.0;
int dacValue=0;
const int numOfBits = 10;
float sinWaveRange = pow(2.0, double(numOfBits)) - 1;

const float minFreq = 2 * PI * 0.1 * 1000; // in rad/s multiplied by 1000 for map()
const float maxFreq = 2 * PI * 4.0 * 1000; // in rad/s multiplied by 1000 for map()

int pinsList[numOfBits] = {3,4,5,6,7, 8, 9, 10, 11, 12}; 
int D[numOfBits];
int sayi;

#define dacOut A2
#define freqPot A6
float filteredValue = 0.0;
float alpha = 0.1; // Filtering constant (smaller values = more filtering)
void setup()
{
  Serial.begin(9600);
  for (int i=0; i<numOfBits; i++)
  {
    pinMode(pinsList[i], OUTPUT);
  }
  pinMode(dacOut, INPUT);
  pinMode(freqPot, INPUT);
}

void loop()
{
  omega = (float) map(analogRead(freqPot), 0, 1023, minFreq, maxFreq) / 1000.0;
  // Map sine wave (-1 to 1) to DAC range (0 to 1024 for 10-bit)
  sineValue = float( sin( omega * (float(micros()) / 1e6) ) );
  sayi =  int(sinWaveRange * 0.5 * (sineValue + 1.0));
  
  // Whatever the hell this is
  D[9] = sayi/512;
  sayi -= D[9]*512;
  D[8] = sayi/256;
  sayi -= D[8]*256;
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

  for (int i=3; i<13; i+=1)
  {
      digitalWrite(i, D[7-(i-5)]);
  }
  
  filteredValue = (alpha * analogRead(dacOut)) + ((1 - alpha) * filteredValue);
  Serial.println(filteredValue);
}
