int b = 5;
void setup() {
    Serial.begin(9600);
    pinMode(b, INPUT);
    pinMode(BUILTIN_LED, OUTPUT);
    for (int i = 0; i < 20; i++)
  {
    digitalWrite(BUILTIN_LED, LOW);
    delay(100);
    digitalWrite(BUILTIN_LED, HIGH);
    delay(100);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int btn = analogRead(b);
  Serial.println(btn);
}
