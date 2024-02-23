#define brightnessPot A0
#define speedPot A7
#define MIN_LED 9
#define MAX_LED 12

const int k_ms = 100000 / (MAX_LED - MIN_LED + 1);

void setup()
{
  Serial.begin(9600);
  pinMode(brightnessPot, INPUT);
  pinMode(speedPot, INPUT);

  for (int i=MIN_LED ; i<MAX_LED; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  for (int i=MIN_LED; i<=MAX_LED; i++)
  {
    analogWrite(i, map(analogRead(brightnessPot), 0, 1023, 102.3, 1023));
    if (i != MIN_LED)
    {
      digitalWrite(i-1, LOW);
    }
    delay(k_ms/(map(analogRead(speedPot), 0, 1023, 200, 1000)));
  }

  for (int i=MAX_LED; i>=MIN_LED; i--)
  {
    analogWrite(i, map(analogRead(brightnessPot), 0, 1023, 102.3, 1023));
    if (i != MAX_LED)
    {
      digitalWrite(i+1, LOW);
    }
    delay(k_ms/(map(analogRead(speedPot), 0, 1023, 200, 1000)));
  }
  Serial.print("Delay: ");
  Serial.println(k_ms/(map(analogRead(speedPot), 0, 1023, 200, 1000)));
  Serial.print("Brightness: ");
  Serial.println(map(analogRead(brightnessPot), 0, 1023, 102.3, 1023));
}
// f = 1/T --> T = 1/f
// --> 1/10 = 0.1s
// number_of_leds * 2 * delay = T
// --> delay = (1000 / (f * number_of_leds))
// OR delay = (1000 * k) / f
