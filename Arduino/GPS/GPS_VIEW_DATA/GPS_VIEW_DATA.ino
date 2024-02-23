void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() 
{
  if (Serial1.available())
  {
    Serial.print((char )Serial1.read());
  }
}
