int sensorPin = A0;
int sensorValue = 0;
void setup() {
  Serial.begin(1200);
}
void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  delay(300);
}
