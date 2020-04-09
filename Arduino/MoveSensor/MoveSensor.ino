
#include <TM1637Display.h>
#include <ESP8266WiFi.h>
// Module connection pins (Digital Pins)
#define CLK D6
#define DIO D7
#define LS A0

TM1637Display display(CLK, DIO);

char ssid[] = "TOPmi";           // SSID of your home WiFi
char password[] = "wifigenius12431243";            // password of your home WiFi

const int inputWindow = 1000;
unsigned int inputSample; 

const int btnPin = D2;
const int relayPin = D1;
int soundBorder = 80; 
int mod = 0; // 0 - regular, 1 - on, 2 - of
int mov = 0;
int btn = 0;
int timer = 0;

WiFiServer server(80);

void setup() {
    Serial.begin(9600);
    pinMode(LS, INPUT);
    pinMode(btnPin, INPUT);
    pinMode(relayPin, OUTPUT);
    display.setBrightness(0x0a);
    display.showNumberDec(8888); 
    Serial.println("READY");

    setupWiFi();
}

void loop(){
  switchMod();
  if (WiFi.status() != WL_CONNECTED)
    setupWiFi();
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      Serial.println(".");
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client: "); Serial.println(request);
      client.flush();
      if ((request.indexOf("on") != -1)){
        mod = 2;
        On();
      }
      else if ((request.indexOf("off") != -1)){
        mod = 1;
        Off();
      }
      else if ((request.indexOf("auto") != -1)){
        mod = 0;
        CountSoundDelta();
        Auto();
      }
      else if ((request.indexOf("reset") != -1)){
        timer = 0;
      }
    }
    client.stop();                // tarminates the connection with the client
  }
}

void On()
{
  timer = 0;
  digitalWrite(relayPin, LOW);
  display.showNumberDec(1);
  delay(50);
}

void Off()
{
  timer = 0;
  digitalWrite(relayPin, HIGH);
  display.showNumberDec(0);
  delay(50);
}

void Auto()
{
  if (timer > 0)
        timer--;
  if (mov == 1)
  {
     digitalWrite(relayPin, LOW);
     timer = 2400;
  }
  if (timer == 0 && mov == 0)
  {
    digitalWrite(relayPin, HIGH);
  }
  display.showNumberDec(timer);
}

void CountSoundDelta()
{
  unsigned int inputMax = 0;
  unsigned int inputMin = 1024;
  int soundDelta = 0;
    for (unsigned int i = 0; i < inputWindow; i++) {
      // read in a single value
      inputSample = analogRead(LS);
      // get the minimum and maximum value
      inputMin = std::min(inputMin, inputSample);
      inputMax = std::max(inputMax, inputSample);
    }
    soundDelta = inputMax - inputMin;
    //Serial.println(soundDelta);
    if (soundDelta >= soundBorder)
    {
      mov = 1;
    }
    else
    {
      mov = 0;  
    }
}

void setupWiFi(){
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());  // some parameters from the network
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());
  Serial.print("Networks: "); Serial.println(WiFi.scanNetworks());
}
void switchMod(){
  btn = digitalRead(btnPin);
    switch(mod) 
    {
      case 0:
        CountSoundDelta();
        Auto();
      break;
      case 1:
        Off();
      break;
      case 2:
        On();
      break;
    }

    if (btn == HIGH)
    {
      mod++;
      if(mod > 2)
        mod = 0;
      delay(500); 
    }
}
