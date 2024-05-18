


const int motorB=11, IN3=12, IN4=13;
const int encoderB=3, encoderA=2;
volatile long int pos=0, lastPos, currentPos;
float speedRPM=0.0;

const int pot=A3;
float error=0.0, outputPID=0.0, integral=0.0, dt;
const float Kp=0.5, Ki=10.0, Kd=0.0;
unsigned long currT=0, prevT=0;
 
unsigned long nowMillis=0, prevMillis=0, deltaT;

void setup()
{
  Serial.begin(9600);

  pinMode(motorB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(pot, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(encoderB), encoderISR, RISING);

  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}

void loop()
{
  currentPos = pos;
  nowMillis = millis();
  deltaT = nowMillis - prevMillis;
  if (deltaT >= 40)
  {
    speedRPM = float(currentPos - lastPos)*200.0/float(deltaT);
    lastPos=currentPos;
    Serial.print("Potentiometer: ");
    Serial.print(analogRead(pot)*0.5);
    Serial.print(",");
    Serial.print("Speed: ");
    Serial.println(speedRPM);

    prevMillis = nowMillis;
  }

  currT = micros();
  dt = float(currT-prevT);
  error = analogRead(pot)*0.5-speedRPM;
  integral += error*dt/1.0e6;
  outputPID = Kp*error + Ki*integral;
  proccesOutput();
  analogWrite(motorB, outputPID);
  prevT=currT;
}

void proccesOutput()
{
  if (outputPID<0)
  {
    digitalWrite(IN3, 0);
    digitalWrite(IN4, 1);
  }
  else
  {
    digitalWrite(IN3, 1);
    digitalWrite(IN4, 0);
  }
  outputPID = fabs(outputPID);
  if (outputPID>255)
  {
    outputPID=255;
  }
}

void encoderISR()
{
  if (digitalRead(encoderA))
  {
    pos++;
  }
  else
  {
    pos--;
  }
}
