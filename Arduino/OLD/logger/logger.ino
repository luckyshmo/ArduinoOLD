#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <TM1637Display.h>
#include <SPI.h>
#include <SD.h>

RTC_DS1307 rtc;
#define DHTPIN 6
#define LIGHTSENSOR 7
#define CLK 9
#define DIO 8
#define HUMIDITYSENSOR A0
#define DHTTYPE           DHT22     // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);
TM1637Display display(CLK, DIO);
File dataFile;

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 4;

void setup() {
  Serial.begin(57600);

  pinMode(LIGHTSENSOR, INPUT);
  pinMode(SS, OUTPUT);
  
  dht.begin();

  display.setBrightness(0x0a);
  display.showNumberDec(8888);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1) ;
  }
  // Open up the file we're going to log to!
  dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (! dataFile) {
    Serial.println("error opening datalog.txt");
    // Wait forever since we cant write data
    while (1) ;
  }
  
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

}

void loop() {
  String dataString = "";
  DateTime now = rtc.now();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int LS = digitalRead(LIGHTSENSOR);
  dataString = now.day() + '.' + now.month() + '.' + now.year() + ' ' + now.hour() + ':' + now.minute() + ':' + now.second() + ' ' + String(h) + ',' + String(t) + ' ' + LS;
  Serial.println(dataString);
  display.showNumberDec(int(t + 0.5));

  dataFile.println(dataString);
  // The following line will 'save' the file to the SD card after every
  // line of data - this will use more power and slow down how much data
  // you can read but it's safer! 
  // If you want to speed up the system, remove the call to flush() and it
  // will save the file only every 512 bytes - every time a sector on the 
  // SD card is filled with data.
  dataFile.flush();

  delay(500);

}
