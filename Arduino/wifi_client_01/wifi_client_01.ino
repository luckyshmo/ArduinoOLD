/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Sends and receives message from the server in every 2 seconds
 *  Communicates: wifi_server_01.ino
 */ 
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte ledPin = 2;
char ssid[] = "TOPmi";           // SSID of your home WiFi
char pass[] = "wifigenius12431243";            // password of your home WiFi
//String pAnswer = "Hello!"; //previous answer
String answer = "Hello!"; 

unsigned long askTimer = 0;

IPAddress server(192,168,31,18);       // the fix IP address of the server
WiFiClient client;

void setup() {
  // initialize the LCD
  lcd.begin(0,2);  // sda=0 | D3, scl=2 | D4

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Hello, world!");
  Serial.begin(115200);               // only for debug
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    lcd.print("Conecting");
    lcd.setCursor(0, 0);
    delay(500);
  }
/*  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());*/
  pinMode(ledPin, OUTPUT);
}

void loop () {
  client.connect(server, 80);   // Connection to the server
  digitalWrite(ledPin, LOW);    // to show the communication only (inverted logic)
  //Serial.println(".");
  client.println("Hello server! Are you sleeping?\r");  // sends the message to the server
  lcd.setCursor(0, 0);
  lcd.print("SuperInfoDisplay");
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  //Serial.println("from server: " + answer);
  lcd.setCursor(0, 1);
  lcd.print(answer);
  client.flush();
  digitalWrite(ledPin, HIGH);
  delay(2000);                  // client will trigger the communication after two seconds
}
