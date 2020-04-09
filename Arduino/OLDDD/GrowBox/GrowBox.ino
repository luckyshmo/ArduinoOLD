#include <LiquidCrystal.h>  // Лобавляем необходимую библиотеку
#include "DHT.h"
LiquidCrystal lcd(13, 12, 14, 4, 5, 16); // (RS, E, DB4, DB5, DB6, DB7)
int Relay_1 = 15; //4 - бок
int Relay_2 = 2; //2 - низ
int Relay_3 = 0; //3 - верх
int DHTPIN = 3;
DHT dht(DHTPIN, DHT22);
int flag = 0;

void setup(){ 
  lcd.begin(16, 2);                  // Задаем размерность экрана

  lcd.setCursor(0, 0);              // Устанавливаем курсор в начало 1 строки
  lcd.print("On");       // Выводим текст
  //lcd.setCursor(0, 1);              // Устанавливаем курсор в начало 2 строки
  //lcd.print("zelectro.cc");         // Выводим текст
  dht.begin();
  onlyTop();
}

void loop(){
  //Считываем влажность
  float h = dht.readHumidity();
  // Считываем температуру
  float t = dht.readTemperature();
  // Проверка удачно прошло ли считывание.
  if (isnan(h) || isnan(t)) {
    lcd.setCursor(0, 0);
    lcd.print("NaN"); 
    return;
  }
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" *C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(h);
  lcd.print("%");
  flag++;
  if(flag > 20)
    bottomTop();
  else
    onlyTop();
  delay(2000);
  if (flag > 40)
    flag = 0;
}

void allOn(){
  digitalWrite(Relay_1, LOW);
  digitalWrite(Relay_2, LOW);
  digitalWrite(Relay_3, LOW);
}

void allOff(){
  digitalWrite(Relay_1, HIGH);
  digitalWrite(Relay_2, HIGH);
  digitalWrite(Relay_3, HIGH);
}

void onlyTop(){
  digitalWrite(Relay_1, HIGH);
  digitalWrite(Relay_2, HIGH);
  digitalWrite(Relay_3, LOW);
}
void bottomTop(){
  digitalWrite(Relay_1, HIGH);
  digitalWrite(Relay_2, LOW);
  digitalWrite(Relay_3, LOW);
}


