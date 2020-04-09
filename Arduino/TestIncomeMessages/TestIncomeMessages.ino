#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
char ssid[] = "TOPmi";           // SSID of your home WiFi
char password[] = "wifigenius12431243";            // password of your home WiFi
WiFiServer server(80);
void setup() {
  lcd.begin(0,2);  // sda=0 | D3, scl=2 | D4

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("Hello, world!");
  Serial.begin(115200);
  setupWiFi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED)
    setupWiFi();
  WiFiClient client = server.available();
  if (client) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Client!");
    if (client.connected()) {
      lcd.setCursor(0, 1);
      lcd.print("ClientConnected");
      String request = client.readStringUntil('\r');    // receives the message from the client
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("From client: ");
      lcd.setCursor(0, 1);
      lcd.print(request);
      //Serial.print("From client: "); Serial.println(request);
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
  lcd.setCursor(0, 0);
  lcd.print(WiFi.localIP());
  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());  // some parameters from the network
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());
  Serial.print("Networks: "); Serial.println(WiFi.scanNetworks());
}
