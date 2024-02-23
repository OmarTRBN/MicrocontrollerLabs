//int encoder, eskiSayi, sigA, sigB;
//
//void setup() 
//{
//  pinMode(2, INPUT);
//  pinMode(3, INPUT);
//  
//  attachInterrupt(2, encode, CHANGE);
//  attachInterrupt(3, encode, CHANGE);
//  eskiSayi = 2*digitalRead(2) + digitalRead(3);
//}
//
//void loop()
//{
//
//}
//
//void encode()
//{
//  sigA = digitalRead(2);
//  sigB = digitalRead(3);
//
//  int sayi = 2*digitalRead(2) + digitalRead(3);
//
//  if (sayi==3)
//    if (eskiSayi==2)
//      encoder++;
//    else
//      encoder--;
//  // else if (sayi==2)
//  // ...
//  // ...
//  // ...
//  // ...
//
//
//  eskiSayi = sayi;
//}

int encoder, eskiSayi;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() 
{
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  
  Serial.begin(9600);
  attachInterrupt(0, encode, CHANGE);
  attachInterrupt(1, encode, CHANGE);
  eskiSayi = 2*digitalRead(2) + digitalRead(3);
}

void loop()
{
  Serial.println(encoder);
  delay(1000);

}

void encode() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastDebounceTime > debounceDelay) {
    int sayi = 2 * digitalRead(2) + digitalRead(3);
    // Serial.print("Hesplanan ");
    // Serial.println(sayi);

    if (sayi == 3) {
      if (eskiSayi == 2)
        encoder++;
      else
        encoder--;
    } else if (sayi == 2) {
      if (eskiSayi == 3)
        encoder--;
      else if (sayi == 0)
        encoder++;
    } else if (sayi == 0) {
      if (eskiSayi == 1)
        encoder++;
      else
        encoder--;
    } else { // Sayi == 1
      if (eskiSayi == 0)
        encoder--;
      else
        encoder++;
    }

    eskiSayi = sayi;
    lastDebounceTime = currentMillis;
  }
}
