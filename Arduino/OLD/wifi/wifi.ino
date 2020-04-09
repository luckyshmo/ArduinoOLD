#include <ESP8266WiFi.h>
 
const char* ssid = "tushata";
const char* password = "wifigenius12431243";
#include "DHT.h"

#define DHTPIN 12 // номер пина, к которому подсоединен датчик
int speakerPin = 14;
int Relay = 13;
float t, h;
int value = HIGH;
WiFiServer server(80);
DHT dht(DHTPIN, DHT22);
int dl = 0;
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode (speakerPin, OUTPUT);
  pinMode(Relay, OUTPUT); 
  dht.begin();
  h = dht.readHumidity(); //Считываем влажность
  t = dht.readTemperature(); // Считываем температуру
 
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
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  // Match the request
 
  if ((request.indexOf("/poliv") != -1) && value == HIGH){
    digitalWrite (Relay, HIGH);
    value = LOW;
  }
  else if ((request.indexOf("/poliv") != -1) && value == LOW){
    digitalWrite (Relay, LOW);
    value = HIGH;
  }
  // Return the response
  output(client);
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
 
}
void output(WiFiClient client)
{
  
  h = dht.readHumidity(); //Считываем влажность
  t = dht.readTemperature(); // Считываем температуру
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  
  client.println("<br><br>");
  client.println("Click <a href=\"/refreh\">here</a> refresh<br>");
  client.println("Click <a href=\"/poliv\">here</a> poliv<br>");
  client.print("Temp is ");
  client.println(t);
  client.print("Hum is ");
  client.println(h);
  
  client.println("</html>");
}
