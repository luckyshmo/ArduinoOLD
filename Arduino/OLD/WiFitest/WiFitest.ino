#include<ESP8266WiFi.h>

// WiFi Definitions
const char* ssid = "LivingRoom";
const char* password = "wifigenius12431243"; // has to be longer than 7 chars
const char* value = "";

int ledPin = 13; // GPIO13
WiFiServer server(80);

void setup() {

   Serial.begin(115200);
   delay(10);
   pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin, HIGH); // turn on

   WiFi.mode(WIFI_AP);
   WiFi.softAP(ssid, password, 1, 1);
  
   server.begin();
   Serial.println("done");
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check of client has connected
  WiFiClient client = server.available();
  if(!client) {
    return;
  }

  // Read the request line
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  // Match request
  if(request.indexOf("/led/on") != -1) {
     digitalWrite(ledPin, HIGH);
     value = "on";
  } else if (request.indexOf("/led/off") != -1) {
     digitalWrite(ledPin, LOW);
      value = "off";
  }
  
  client.flush();
   
  // JSON response
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: application/json\r\n\r\n";
  s += "{\"data\":{\"message\":\"success\",\"value\":\"";
  s += value;
  s += "\"}}\r\n";
  s += "\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disconnected");

  // The client will actually be disconnected when the function returns and the client object is destroyed
}
