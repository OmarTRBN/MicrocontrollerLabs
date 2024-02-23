#define brightnessPot A0
#define speedPot A7
#define MIN_LED 9
#define MAX_LED 12

void setup()
{
  // Serial.begin(9600);
  pinMode(brightnessPot, INPUT);
  pinMode(speedPot, INPUT);

  for (int i=MIN_LED ; i<MAX_LED; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  // Serial.println(analogRead(brightnessPot));
  // Serial.println(analogRead(speedPot));
  for (int i=MIN_LED+1; i<=MAX_LED; i++)
  {
    analogWrite(i-1, analogRead(brightnessPot) * 0.25);
    analogWrite(i, analogRead(brightnessPot) * 0.25);
    if (i != MIN_LED)
    {
      digitalWrite(i-2, LOW);
    }
    delay(100 + analogRead(speedPot));
  }

  for (int i=MAX_LED; i>=MIN_LED+1; i--)
  {
    analogWrite(i-1, analogRead(brightnessPot) * 0.25);
    analogWrite(i, analogRead(brightnessPot) * 0.25);
    if (i != MAX_LED)
    {
      digitalWrite(i+1, LOW);
    }
    delay(100 + analogRead(speedPot));
  }
}

