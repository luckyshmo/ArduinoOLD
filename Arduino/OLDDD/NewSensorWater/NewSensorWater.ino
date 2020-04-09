#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 7
#define DIO 5

TM1637Display display(CLK, DIO);

byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin       = 2;
#define RELAY1  13
#define button 12
int buttonState = 0; 
void on()
{
  digitalWrite(RELAY1, HIGH);
}
void off()
{
  digitalWrite(RELAY1, LOW);
}

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;
float cof = 18;

volatile byte pulseCount;  

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;

void setup()
{
  display.setBrightness(0x0a);
  display.showNumberDec(1111);
  pinMode(button, INPUT);
  pinMode(RELAY1, OUTPUT);
  //off();
  // Initialize a serial connection for reporting values to the host
  Serial.begin(38400);
  
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
  // Configured to trigger on a FALLING state change (transition from HIGH
  // state to LOW state)
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  on();
}

/**
 * Main program loop
 */
void loop()
{
  if((millis() - oldTime) > 1000)    // Only process counters once per second
  { 
      detachInterrupt(sensorInterrupt);
      flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
      oldTime = millis();
      flowMilliLitres = (flowRate / 60) * 1000;
      totalMilliLitres += flowMilliLitres;
        
      unsigned int frac;
      Serial.print("Flow rate: ");
      Serial.print(int(flowRate));  // Print the integer part of the variable
      Serial.print(".");             // Print the decimal point
      // Determine the fractional part. The 10 multiplier gives us 1 decimal place.
      frac = (flowRate - int(flowRate)) * 10;
      Serial.print(frac, DEC) ;      // Print the fractional part of the variable
      Serial.print("L/min");
      // Print the number of litres flowed in this second
      Serial.print("  Current Liquid Flowing: ");             // Output separator
      Serial.print(flowMilliLitres);
      Serial.print("mL/Sec");
  
      // Print the cumulative total of litres flowed since starting
      Serial.print("  Output Liquid Quantity: ");             // Output separator
      Serial.print(totalMilliLitres/cof);
      Serial.println("mL"); 
      display.showNumberDec(totalMilliLitres/cof);
  
      // Reset the pulse counter so we can start incrementing again
      pulseCount = 0;
      buttonState = digitalRead(button);
      Serial.println(buttonState);
      if (totalMilliLitres/cof > 1000)
      {
        Serial.println(">500");
        off();  
        if (buttonState == HIGH){
          totalMilliLitres = 0;
          on();
        }
      }
      
      // Enable the interrupt again now that we've finished sending output
      attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }
}

/*
Insterrupt Service Routine
 */
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
