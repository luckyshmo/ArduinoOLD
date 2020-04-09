#include <ESP8266WiFi.h>
 
const char* ssid = "tushata";
const char* password = "wifigenius12431243";
#include "DHT.h"

int Relay_2 = 13; //низ
int Relay_3 = 14; //верх
int Relay_4 = 12; //бок
int DHTPIN = 4;
float t, h;
DHT dht(DHTPIN, DHT22);
int flag = 0; //для работы куллеров снизу 
int value = HIGH;

WiFiServer server(80);
int dl = 0;
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(Relay_2, OUTPUT);     
  pinMode(Relay_3, OUTPUT);     
  pinMode(Relay_4, OUTPUT);          
  onlyTop();
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
  flag++;
  if(flag > 200)
    bottomTop();
  else
    onlyTop();
  delay(200);
  if (flag > 400)
    flag = 0;
  
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
    //digitalWrite (Relay, HIGH);
    value = LOW;
  }
  else if ((request.indexOf("/poliv") != -1) && value == LOW){
    //digitalWrite (Relay, LOW);
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
void allOn(){
  digitalWrite(Relay_2, LOW);
  digitalWrite(Relay_3, LOW);
  digitalWrite(Relay_4, LOW);
}

void allOff(){
  digitalWrite(Relay_2, HIGH);
  digitalWrite(Relay_3, HIGH);
  digitalWrite(Relay_4, HIGH);
}

void onlyTop(){
  digitalWrite(Relay_2, HIGH);
  digitalWrite(Relay_3, LOW);
  digitalWrite(Relay_4, HIGH);
}
void bottomTop(){
  digitalWrite(Relay_2, LOW);
  digitalWrite(Relay_3, LOW);
  digitalWrite(Relay_4, HIGH);
}
