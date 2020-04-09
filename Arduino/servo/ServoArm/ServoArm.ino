/*
  SweepTwoServos
  By Philip van Allen <philvanallen.com> for the VarSpeedServo.h library (October 2013)
  This example code is in the public domain
  
  Sweep two servos from 0-180, 180-0 in unison
  Uses the wait feature of the 2013 version of VarSpeedServo to start the first servo moving in the background
  and immediately starting a second servo moving and waiting for the second one to finish.
  
  Note that two servos will require more power than is available from the USB port - use an external power supply!
*/

#include <VarSpeedServo.h> 
 
VarSpeedServo claw;  
VarSpeedServo shoulder;
VarSpeedServo elbow;
VarSpeedServo base;
 
const int clawPin = 4; // the digital pin used for the first servo
const int shoulderPin = 3; // the digital pin used for the second servo
const int elbowPin = 2; 
const int basePin = 5; 
 
void setup() { 
  Serial.begin(9600);
  claw.attach(clawPin);  // 20-70
  claw.write(45,5,false); // set the intial position of the servo, as fast as possible, run in background
  shoulder.attach(shoulderPin);  // 100-170
  shoulder.write(170,50,false);  // set the intial position of the servo, as fast as possible, wait until done
  elbow.attach(elbowPin);  // 20-100
  elbow.write(20,50,false);  // set the intial position of the servo, as fast as possible, wait until done*/
  base.attach(basePin); //45-135
  base.write(90,10,false);  // set the intial position of the servo, as fast as possible, wait until done
  Serial.println("preset done");
  delay(5000);
} 

void loop() {
  Serial.println("1");
  claw.write(45,25,false); 
  shoulder.write(135,25,false);  
  //elbow.write(60,25,false);  
  base.write(80,25,false);
  Serial.println("2");
  delay(2000);
  Serial.println("3");
  claw.write(20,25,false); 
  shoulder.write(110,5,false);  
  //elbow.write(80,5,false);  
  base.write(100,10,false);
  Serial.println("4");
  delay(2000);
} 
