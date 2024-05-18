#include "motorDriver.h"

#define enA 4
#define enB 5
#define in1 30
#define in2 32
#define in3 34
#define in4 36
#define motA_encA 2
#define motB_encA 3
#define motA_encB 6
#define motB_encB 7

MotorDriver SlackMd(enA, enB, in1, in2, in3, in4);

void setup()
{
  SlackMd.beginMotorDriver();
  Serial.begin(9600);
}

void loop()
{
  SlackMd.forward();
  SlackMd.setPWMValue(60, 60);
  Serial.print("POSITION: ");
//  Serial.println(SlackMd.pos_motA);
}
