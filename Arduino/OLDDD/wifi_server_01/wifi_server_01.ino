/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Starts WiFi server with fix IP and listens
 *  Receives and sends messages to the client
 *  Communicates: wifi_client_01.ino
 */
#include <SPI.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <TM1637Display.h>
#define CLK D6
#define DIO D5

TM1637Display display(CLK, DIO);

int DHTPIN = D4;

DHT dht(DHTPIN, DHT22);

byte ledPin = 2;
char ssid[] = "wifi_2.4G";               // SSID of your home WiFi
char pass[] = "wifigenius12431243";               // password of your home WiFi
WiFiServer server(80);                    

IPAddress ip(192.168.5.111);            // IP address of the server
IPAddress gateway(192,168,5,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network

void setup() {
  display.setBrightness(0x0a);
  display.showNumberDec(1111);
  Serial.begin(115200);                   // only for debug
  //WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  WiFi.begin(ssid, pass);                 // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  server.begin();                         // starts the server
  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());  // some parameters from the network
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());
  Serial.print("Networks: "); Serial.println(WiFi.scanNetworks());
  pinMode(ledPin, OUTPUT);
  Serial.println("conected");
  dht.begin();
}

void loop () {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  display.showNumberDec(t);
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      digitalWrite(ledPin, LOW);  // to show the communication only (inverted logic)
      Serial.println(".");
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client: "); Serial.println(request);
      client.flush();
      
      if (isnan(h) || isnan(t)) {
        client.println("NaN"); 
        return;
      }
      else
      {        
        client.println(String(t) + " " + String (h) + "\r");
      }
       // sends the answer to the client
      digitalWrite(ledPin, HIGH);
    }
    client.stop();                // tarminates the connection with the client
  }
}
