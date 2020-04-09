#include "DHT.h"

#define DHTPIN 12 // номер пина, к которому подсоединен датчик
int speakerPin = 14;
// Раскомментируйте в соответствии с используемым датчиком

// Инициируем датчик

DHT dht(DHTPIN, DHT22);

void setup() {
pinMode (speakerPin, OUTPUT);

Serial.begin(9600);

dht.begin();

}

void loop() {

// Задержка 2 секунды между измерениями

delay(2000);

//Считываем влажность
float h = dht.readHumidity(); //Считываем влажность
float t = dht.readTemperature(); // Считываем температуру

// Проверка удачно прошло ли считывание.

if (isnan(h) || isnan(t)) 
{
  Serial.println("Не удается считать показания");
  return;
}

Serial.print("Hum: ");
Serial.println(h);
Serial.print("Temp: ");
Serial.println(t);
if (t > 25)
{
  analogWrite (speakerPin, 255);
  delay (1000);
  analogWrite (speakerPin, 0);
  delay (500);
}

}

