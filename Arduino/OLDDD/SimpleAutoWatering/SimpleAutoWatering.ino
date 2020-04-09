
#include <ESP8266WiFi.h>
 
const char* ssid = "ASUS";
const char* password = "wifigenius12431243";
#include "DHT.h"

int DHTPIN = D8; //dht22
int Relay_1 = 16; // first pump
int Relay_2 = 5; //
int Relay_3 = 4; //
int Relay_4 = 14; //
int Sensor_1 = 12; // first water sensor
int val = 0;
float t, h; //temperature, humidity

DHT dht(DHTPIN, DHT22);
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
   Serial.print("Start");
  delay(10);
  pinMode(Relay_1, OUTPUT);     
  pinMode(Relay_2, OUTPUT);     
  pinMode(Relay_3, OUTPUT);   
  pinMode(Relay_4, OUTPUT);
  pinMode(Sensor_1, INPUT);
  dht.begin();
  h = dht.readHumidity(); //Считываем влажность
  t = dht.readTemperature(); // Считываем температуру
  allOff();

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
  h = dht.readHumidity(); //Считываем влажность
  t = dht.readTemperature(); // Считываем температуру
  val = digitalRead(Sensor_1); 
  if (val == 1)
  {
    allOn();
  }
  else
  {
    allOff();
  }

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
 
  if ((request.indexOf("/poliv") != -1)){
    allOn();
    delay(1000);
    allOff();
  }
  
  output(client);
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}

void allOn(){
  digitalWrite(Relay_1, LOW);
  digitalWrite(Relay_2, LOW);
  digitalWrite(Relay_3, LOW);
  digitalWrite(Relay_4, LOW);
}

void allOff(){
  digitalWrite(Relay_1, HIGH);
  digitalWrite(Relay_2, HIGH);
  digitalWrite(Relay_3, HIGH);
  digitalWrite(Relay_4, HIGH);
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
