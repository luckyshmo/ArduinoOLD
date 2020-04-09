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
WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  dht.begin();
  setupWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED)
    setupWiFi();
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      String request = client.readStringUntil('\r');    // receives the message from the clien
      Serial.print("From client: "); Serial.println(request);
      if ((request.indexOf("on") != -1)){
        On();
      }
      else if ((request.indexOf("off") != -1)){
        Off();
      }
      if ((request.indexOf("t") != -1))
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
        }
        
      }
      client.flush();
    }
    client.stop();                // tarminates the connection with the client
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
void On()
{
  digitalWrite(relayPin, LOW);
}

void Off()
{
  digitalWrite(relayPin, HIGH);
}
