// Pin assignments
#define omega 0.001570795  // 2*pi*f = 2*3.14159 * 0.25

const int potPin2 = A10; // Potentiometer connected to analog pin A9
int sayi;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
//  int omega = 6.28*analogRead(A10);  
  sayi=int(127.5*(sin(omega * float(millis())) + 1.0));
  Serial.println(sayi);
  delay(1);
}
