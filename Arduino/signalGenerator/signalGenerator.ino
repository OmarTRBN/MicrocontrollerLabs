
float omega = 0;
float sineValue=0.0;
int dacValue=0;
const int numOfBits = 10;
float sinWaveRange = pow(2.0, double(numOfBits)) - 1;

const float minFreq = 2 * PI * 0.1 * 1000; // in rad/s multiplied by 1000 for map()
const float maxFreq = 2 * PI * 10.0 * 1000; // in rad/s multiplied by 1000 for map()

int pinsList[numOfBits] = {3,4,5,6,7, 8, 9, 10, 11, 12}; 
int D[numOfBits];

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
  dacValue =  int(sinWaveRange * 0.5 * (sineValue + 1.0));
  
  for (int i = 0; i < numOfBits; i++) {
    digitalWrite(pinsList[i], (dacValue >> (numOfBits - 1 - i)) & 1);
  }

  // Digital low pass filter
  filteredValue = (alpha * analogRead(dacOut)) + ((1 - alpha) * filteredValue);
  Serial.println(filteredValue);
}
