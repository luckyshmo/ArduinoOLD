#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK D6
#define DIO D5
#define LS A0

const int inputWindow = 1500;
unsigned int inputSample;

TM1637Display display(CLK, DIO);

void setup()
{
  pinMode(LS, INPUT);
  display.setBrightness(0x0a);  //set the diplay to maximum brightness
}

void loop()
{
  unsigned int inputMax = 0;
  unsigned int inputMin = 1024;
  for (unsigned int i = 0; i < inputWindow; i++) {
    // read in a single value
    inputSample = analogRead(LS);
    // get the minimum and maximum value
    inputMin = min(inputMin, inputSample);
    inputMax = max(inputMax, inputSample);
  }
  display.showNumberDec(inputMax - inputMin); //Display the Variable value;
}
