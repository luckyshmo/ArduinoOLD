// Joystick x- and y- axes are connected to A1 and A0 analog pins of Arduino.
// Servos are connectd to PWM Pins 9 and 10.


#include <Servo.h>

Servo claw, shoulder, elbow, base; 

int joy1X = A1; //  X - axis of Joystick
int joy1Y = A0; // y - axis of Joystick
int joy2X = A3; //  X - axis of Joystick
int joy2Y = A2; // y - axis of Joystick
int x1, y1, x2, y2; 
const int clawPin = 4; // the digital pin used for the first servo
const int shoulderPin = 3; // the digital pin used for the second servo
const int elbowPin = 2; 
const int basePin = 5; 


void setup()
{ 
  Serial.begin(9600);
  claw.attach(clawPin);  // 20-70
  //claw.write(45); // set the intial position of the servo, as fast as possible, run in background
  shoulder.attach(shoulderPin);  // 100-170
  //shoulder.write(135);  // set the intial position of the servo, as fast as possible, wait until done
  elbow.attach(elbowPin);  // 20-100 !!!
  //elbow.write(50);  // set the intial position of the servo, as fast as possible, wait until done*/
  base.attach(basePin); //45-135 !!
  //base.write(90);  // set the intial position of the servo, as fast as possible, wait until done
} 

void loop()
{  
  x1 = map(analogRead(joy1X), 0, 1023, 20, 70); 
  y1 = map(analogRead(joy1Y), 0, 1023, 20, 110);
  y2 = map(analogRead(joy2Y), 0, 1023, 10, 80); 
  x2 = map(analogRead(joy2X), 0, 1023, 100, 170);
  claw.write(y2);
  Serial.println("Base pos is " + String(y1));
  base.write(y1);
  shoulder.write(x2); 
  elbow.write(x1);
  delay(5); 
}
