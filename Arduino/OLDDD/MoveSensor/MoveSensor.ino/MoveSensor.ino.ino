

const char* ssid = "StayHigh";
const char* password = "isuckdirtycock";

int pirPin = D4;
int Relay = D1;
int buzzer = D2;
int button = D3;
int val;
int flag = 0;
int buttonVal = 0;
int dl = 0;
int i = 20;

void setup() {
  
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(Relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  val = digitalRead(pirPin); //read state of the PIR
  buttonVal = digitalRead(button);
  if (buttonVal == 1)
  {
    Serial.println("Change type");
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(100);        // ...for 1 sec
    noTone(buzzer);
    flag++;
    if (flag > 2)
      flag = 0;
  }
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
}
