#define rightButtonPin 43
#define leftButtonPin 47

#define MIN_LED 9
#define MAX_LED 12

int currentLed = MIN_LED;

void setup()
{
  pinMode(rightButtonPin, INPUT);
  pinMode(leftButtonPin, INPUT);
  for (int i=MIN_LED ; i<MAX_LED; i++)
  {
    pinMode(i, OUTPUT);
  }

  digitalWrite(MAX_LED, HIGH);
}

void loop()
{
  if (digitalRead(rightButtonPin) == HIGH)
  {
    delay(50); // Debounce delay
    while (digitalRead(rightButtonPin) == HIGH)
    {
      // Wait for button release
    }
    if (currentLed != MAX_LED)
    {
      digitalWrite(currentLed, LOW);
      digitalWrite(currentLed + 1, HIGH);
      currentLed += 1;
    }
    else
    {
      digitalWrite(currentLed, LOW);
      digitalWrite(MIN_LED, HIGH);
      currentLed = MIN_LED;
    }
  }
  if (digitalRead(leftButtonPin) == HIGH)
  {
    delay(50); // Debounce delay
    while (digitalRead(leftButtonPin) == HIGH)
    {
      // Wait for button release
    }
    if (currentLed != MIN_LED)
    {
      digitalWrite(currentLed, LOW);
      digitalWrite(currentLed - 1, HIGH);
      currentLed -= 1;
    }
    else
    {
      digitalWrite(currentLed, LOW);
      digitalWrite(MAX_LED, HIGH);
      currentLed = MAX_LED;
    }
  }
}
