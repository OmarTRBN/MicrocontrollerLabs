#define rightButtonPin 43
#define leftButtonPin 47

#define MIN_LED 10
#define MAX_LED 12

int currentLed = MIN_LED;

void setup()
{
  pinMode(rightButtonPin, INPUT);
  pinMode(leftButtonPin, INPUT);
  for (int i=MIN_LED-1; i<=MAX_LED; i++)
  {
    pinMode(i, OUTPUT);
  }
  digitalWrite(MIN_LED, HIGH);
  digitalWrite(MIN_LED-1, HIGH);
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
      digitalWrite(currentLed-1, LOW);
      digitalWrite(currentLed + 1, HIGH);
      currentLed += 1;
    }
  }
  if (digitalRead(leftButtonPin) == HIGH)
  {
    delay(50); // Debounce delay
    while (digitalRead(leftButtonPin) == HIGH)
    {
      // Wait for button release
    }
    if (currentLed != MIN_LED-1)
    {
      digitalWrite(currentLed + 1, LOW);
      digitalWrite(currentLed - 1, HIGH);
      currentLed -= 1;
    }
  }
}