#include <LiquidCrystal.h>  // Лобавляем необходимую библиотеку
LiquidCrystal lcd(13, 12, 14, 4, 5, 16); // (RS, E, DB4, DB5, DB6, DB7)

void setup(){ 
  lcd.begin(16, 2);                  // Задаем размерность экрана

  lcd.setCursor(0, 0);              // Устанавливаем курсор в начало 1 строки
  lcd.print("Hello, world!");       // Выводим текст
  lcd.setCursor(0, 1);              // Устанавливаем курсор в начало 2 строки
  lcd.print("zelectro.cc");         // Выводим текст
}

void loop(){
}
