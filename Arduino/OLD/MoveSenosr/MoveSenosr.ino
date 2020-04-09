
#include <SerialESP8266wifi.h>

const char* ssid = "StayHigh";
const char* password = "isuckdirtycock";
int i = 20; // interval in ms

int pirPin = 12;
int Relay = 14;
int val;
int flag = 0;
//WiFiServer server(80);
int dl = 0;

void setup() {
  
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(Relay, OUTPUT);
  inputString.reserve(20);
  swSerial.begin(9600);
  while (!Serial)
    ;
  Serial.println("Starting wifi");

  wifi.setTransportToTCP();// this is also default
  // wifi.setTransportToUDP();//Will use UDP when connecting to server, default is TCP

  wifi.endSendWithNewline(true); // Will end all transmissions with a newline and carrage return ie println.. default is true

  wifi.begin();

  //Turn on local ap and server (TCP)
  wifi.startLocalAPAndServer("MY_CONFIG_AP", "password", "5", "2121");

  wifi.connectToAP(ssid, wifipass);
  wifi.connectToServer("192.168.0.28", "2121");
  wifi.send(SERVER, "ESP8266 test app started");
  Serial.println();
  Serial.println();
  
}

void loop() {
  val = digitalRead(pirPin); //read state of the PIR
  if (flag == 2)
  {
    if (val == HIGH)
      i = 600;
    if (i > 0)
    {
      digitalWrite(Relay, HIGH);
      i--;
    }
    else
    {
      digitalWrite(Relay, LOW);
    }
  }
  else if (flag == 1)
  {
    digitalWrite(Relay, LOW);
  }
  else 
  {
    digitalWrite(Relay, HIGH); 
  }
  delay(100);
   //Make sure the esp8266 is started..
  if (!wifi.isStarted())
    wifi.begin();
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client) {
      return;
    }
    // Wait until the client sends some data
    Serial.println("new client");
    while (!client.available()) {
      delay(1);
    }
  
    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    // Match the request
  
    if (request.indexOf("/on") != -1) {
      flag = 1;
    }
    else if (request.indexOf("/off") != -1) {
      flag = 0;
    }
    else if (request.indexOf("/auto") != -1) {
      flag = 2;
    }
    // Return the response
    output(client);
    delay(1);
    Serial.println("Client disconnected");
    Serial.println("");
}
void output(WiFiClient client)
{
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.println("<br><br>");
  client.println("Click <a href=\"/on\">here</a> Aon<br>");
  client.println("Click <a href=\"/off\">here</a> Aoff<br>");
  client.println("Click <a href=\"/auto\">here</a> Auto<br>");
  client.println("</html>");
}
void setupServer() 
{
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
