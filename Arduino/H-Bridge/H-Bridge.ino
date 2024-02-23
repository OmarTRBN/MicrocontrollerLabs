

void setup()
{
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);  
}

void loop()
{
  digitalWrite(5, LOW);
//  analogWrite(6, 50);
  digitalWrite(6, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delay(2000);
  
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(500);
  
//  analogWrite(5, 50);
  digitalWrite(5, HIGH);
  digitalWrite(6, !HIGH);
  digitalWrite(10, !HIGH);
  digitalWrite(11, !LOW);
  delay(2000);
  
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(500);
}
