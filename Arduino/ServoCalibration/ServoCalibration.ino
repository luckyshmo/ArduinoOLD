/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
Servo myservo3;  // create servo object to control a servo
Servo myservo4;  // create servo object to control a servo

int val, from = 5, to = 120;    // variable to read the value from the analog pin

void setup() {
  myservo4.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo3.attach(8);
  myservo2.attach(7);
  myservo1.attach(6); //кисть от 5 до 120
  
  Serial.begin(9600);
  while (from == -1 || to == -1)
  {
    if (Serial.available() > 0) 
    {
      Serial.println("Enter From");
      from = Serial.parseInt();
      Serial.print(from); Serial.print(", Enter To");
      to = Serial.parseInt();
      Serial.println(to);
    }
  }
}

void loop() {
  myservo1.write(from);                  // sets the servo position according to the scaled value
  myservo2.write(from);  
  myservo3.write(from);  
  myservo4.write(from);  
  delay(3000);                           // waits for the servo to get there
  myservo1.write(to);                  
  myservo2.write(to);  
  myservo3.write(to);  
  myservo4.write(to);
  delay(1500);  
}
