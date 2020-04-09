#include <TM1637Display.h>
#include <Wire.h>       //I2C library
#include <RtcDS3231.h>  //RTC library
 
//RtcDS3231 rtcObject;              //Uncomment for version 1.0.1 of the rtc library
RtcDS3231<TwoWire> rtcObject(Wire); //Uncomment for version 2.0.0 of the rtc library
 
const int CLK = D6; //Set the CLK pin connection to the display
const int DIO = D5; //Set the DIO pin connection to the display
const int BUZZ = D7;
 
int numCounter = 0;
 
TM1637Display display(CLK, DIO); //set up the 4-Digit Display.
 
void setup()
{
  pinMode(BUZZ, OUTPUT);
  display.setBrightness(0x0a); //set the diplay to maximum brightness
  Serial.begin(115200);  //Starts serial connection
  rtcObject.Begin();     //Starts I2C
 
  RtcDateTime currentTime = RtcDateTime(16, 05, 18, 21, 20, 0); //define date and time object
  rtcObject.SetDateTime(currentTime); //configure the RTC with object
}
 
 
void loop()
{
  melodi();
  RtcDateTime currentTime = rtcObject.GetDateTime();    //get the time from the RTC
  char str[15];   //declare a string as an array of chars
  sprintf(str, "%d/%d/%d %d:%d:%d",     //%d allows to print an integer to the string
          currentTime.Year(),   //get year method
          currentTime.Month(),  //get month method
          currentTime.Day(),    //get day method
          currentTime.Hour(),   //get hour method
          currentTime.Minute(), //get minute method
          currentTime.Second()  //get second method
         );
 
  Serial.println(str); //print the string to the serial port
  delay(100); //20 seconds delay
  melodi();
 for(numCounter = 0; numCounter < 5; numCounter++) //Iterate numCounter
 {
   display.showNumberDec(numCounter); //Display the numCounter value;
   delay(100);
 }
}

void melodi() {
   Serial.println("PHONE");
  for (int i = 0; i < 100; i++)
  {
  analogWrite(BUZZ, 255);
  delay (200);
  digitalWrite(BUZZ, 50);
  }
}
