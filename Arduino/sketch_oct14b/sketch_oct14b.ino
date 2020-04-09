#include <VarSpeedServo.h>
#include <math.h> 
 
VarSpeedServo base;
VarSpeedServo shoulder;
 
const int basePin = 9;
const int shoulderPin = 10;
 
void setup() { 
  Serial.begin(9600);
  
  base.attach(basePin);
  base.write(90,50,false);
  shoulder.attach(shoulderPin);
  shoulder.write(90,50,false);
    
  Serial.println("preset done");
  delay(3000);
} 

int basePosition = 90;
int shoulderPosition = 90;
void loop() {
  /*while (Serial.available() > 0) 
  {
    char input = Serial.read();
    if (input == 'd' && basePosition <= 135)
    {
      Serial.println("d");
      basePosition+=10;
      base.write(basePosition,25,false);
    }
    if (input == 'a' && basePosition >= 45 )
    {
      Serial.println("a");
      basePosition-=10;
      base.write(basePosition,25,false);
    }
    if (input == 'w' && shoulderPosition <= 135)
    {
      Serial.println("w");
      shoulderPosition+=10;
      shoulder.write(shoulderPosition,25,false);
    }
    if (input == 's' && shoulderPosition >= 90)
    {
      Serial.println("s");
      shoulderPosition-=10;
      shoulder.write(shoulderPosition,25,false);
    }

  }*/
  double delta = 0, delta1 = 0;
  for (int cStep=0; cStep < 45; cStep++)
  {
    delta = 1 * sin(2*PI*cStep/45);
    delta1 = 1 * cos(2*PI*cStep/45);
    base.write(110+delta*20,255,false);
    shoulder.write(110+delta1*20,255,true);
    Serial.print("Sin: ");
    Serial.println(110+delta*15);
    Serial.print("Cos: ");
    Serial.println(110+delta1*15);
    //delay(15);
    //shoulder.write(135,25,false); 
  }
  /*for (int i=135; i > 45; i--)
  {
    delta = 1 * sin(2*PI*basePosition/45);
    basePosition -= delta;
    base.write(basePosition,25,false);
    delay(100); 
  }
  delay(2000);*/
} 
