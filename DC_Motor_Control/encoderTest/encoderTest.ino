#define ENB 11 // PWM control for motor 2
#define IN3 12 // Direction control for motor 2
#define IN4 13 // Direction control for motor 2

const int encoderA = 3;
const int encoderB = 2;

volatile int counterA = 0;
volatile int counterB = 0;
float currentAngle = 0.0;
float rpm=0.0;
unsigned long previousMillis = 0, currentMillis = 0;
int pos=0;
int pot=0;
int power=0;
float error = 0.0;

void setup()
{
  Serial.begin(9600);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(A3, INPUT);
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderA), encoderISRA, RISING);
  
  previousMillis = millis();
  digitalWrite(4, 0);
  pot = 0;
  currentAngle = pot;
  pos = int(currentAngle/1.18421);
}

void loop()
{
//  currentMillis = millis();
//  if (currentMillis - previousMillis >= 500)
//  {
//    previousMillis = millis();
//    Serial.print("Current power: ");
//    Serial.print(power);
//    Serial.print("||||| Current angle: ");
//    Serial.println(currentAngle);
//  }

  Serial.print("Reference:");
  Serial.print(pot);
  Serial.print(",");
//  Serial.print("Power:");
//  Serial.print(power);
//  Serial.print(",");
  Serial.print("Angle:");
  Serial.println(currentAngle);
  
  currentAngle = float(pos)*1.18421; // 360/304=1.82, 304 is encoder PPR
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    if (input.length() > 0) {
      pot = input.toInt();
    }
  }
  
  error = float(pot)- currentAngle;
  power = controllerPID(error);
  
  if (power < 0)
  { // Set CW rotation
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
    power = -1 * power;
  }
  else
  {
    // Set CCW rotation
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
  }
  
  analogWrite(ENB, constrain(power, 20, 255));
}

void encoderISRA()
{
  if (digitalRead(encoderB))
  {
    pos = (pos+1)%304;
  }
  else
  {
    pos = (pos-1)%304;
  }
}

int controllerPID(float error)
{ 
  static unsigned long nowTime = 0;
  static unsigned long prevTime = 0;
  static float dt = 0.0;
    
  static float Kp = 1.0;
  static float Kd = 0.4;
  static float Ki = 2.0;
  
  static float prevError = 0;
  static float beforePrevError = 0;
  static float integralTerm = 0.0;
  static float derivativeTerm = 0.0;

  static int sumPID = 0;
  
  nowTime = millis();
  dt = float(nowTime - prevTime + 0.5) * 0.001;
  prevTime = nowTime;
  
  // Proportional term is error itself
  integralTerm += error*dt;
  derivativeTerm = (3.0*error - 4.0*prevError + beforePrevError) / (2.0*dt);
    
  sumPID = int(error*Kp + integralTerm*Ki + derivativeTerm*Kd + 0.5);
  
  prevError = error;
  beforePrevError = prevError;
  
  return sumPID;
}

void onOffControl(int refAngle)
{
  if (currentAngle < 0)
  {
    // Rotate CW
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
    analogWrite(ENB, 40);
  }
  else
  {
    if (refAngle > currentAngle)
    {
      // Rotate CCW
      digitalWrite(IN3, 1);
      digitalWrite(IN4, 0);
      analogWrite(ENB, 50);  
    }
    else if (refAngle < currentAngle)
    {
      // Rotate CCW
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 1);
      analogWrite(ENB, 50);
    }
    else
    {
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 0);
      analogWrite(ENB, 0);
    }
  }
}
