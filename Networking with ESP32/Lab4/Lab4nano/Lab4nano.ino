// Arduino nano code

// Motor A connections
int enA = 9;
int in1 = 7;
int in2 = 8;
// Motor B connections
int enB = 11;
int in3 = 10;
int in4 = 12;

int rightr = 0;
int leftl = 0;
int active = 0;

void setup()
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  rightr = digitalRead(2);
  leftl = digitalRead(3);
  active = digitalRead(4);

  if (active == 0)
  {
    digitalWrite(in1, 0);
    digitalWrite(in2, LOW);
    digitalWrite(in3, 0);
    digitalWrite(in4, LOW);
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    delay(200);
  }
  else if (rightr == 1 && leftl == 1 && active == 1)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, 128);
    analogWrite(enB, 128);
    delay(200);
  }
  else if (rightr == 1 && leftl == 0 && active == 1)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, 128);
    analogWrite(enB, 128);
    delay(200);    
  }
  else if (rightr == 0 && leftl == 1 && active == 1)
  {
    digitalWrite(in1, 1);
    digitalWrite(in2, 0);
    digitalWrite(in3, 0);
    digitalWrite(in4, 1);
    analogWrite(enA, 128);
    analogWrite(enB, 128);
    delay(200);     
  }
  else if (rightr == 0 && leftl == 0 && active == 1)
  {
    digitalWrite(in1, 0);
    digitalWrite(in2, 1);
    digitalWrite(in3, 0);
    digitalWrite(in4, 1);  
    analogWrite(enA, 128);
    analogWrite(enB, 128);
    delay(200); 
  }
  
  Serial.print("right: ");
  Serial.println(rightr);

  Serial.print("left: ");
  Serial.println(leftl);

  Serial.print("active: ");
  Serial.println(active);
  delay(1000);

  Serial.println("#######################");
}
