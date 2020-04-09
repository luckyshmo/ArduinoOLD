#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Wire.h> 
#include "DHT.h"
char ssid[] = "TOPmi";           // SSID of your home WiFi
char password[] = "wifigenius12431243";            // password of your home WiFi
const int relayPin = D3;
const int DHTPIN = D4;
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

IPAddress server(192,168,31,18);       // the fix IP address of the server
WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  dht.begin();
  setupWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED)
    setupWiFi();
  client.connect(server, 80);   // Connection to the server
  client.println("Hello server! Are you sleeping?\r");  // sends the message to the server
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.print("From client: "); Serial.println(answer);
  if ((answer.indexOf("on") != -1)){
    On();
  }
  else if ((answer.indexOf("off") != -1)){
     Off();
  }
  if ((answer.indexOf("t") != -1))
  {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
          Serial.println("NaN");
    }
    else
    {        
      Serial.print("t, h: "); Serial.print(t); Serial.print(", "); Serial.println(h);
      client.println("T:"+String(t) + ",H:" + String(h) + "\r");
    }              // tarminates the connection with the client
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
void On()
{
  digitalWrite(relayPin, LOW);
}

void Off()
{
  digitalWrite(relayPin, HIGH);
}
