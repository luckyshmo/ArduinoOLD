#include <TM74HC595Display.h>
const int RCLK = 7; //Set the CLK pin connection to the display
const int SCLK = 6; //Set the CLK pin connection to the display
const int DIO = 5; //Set the DIO pin connection to the display
const int LOUDSENSOR = D2;
const int RELE = D1;
const int REDB = D8;
const int GREENB = D0;
TM74HC595Display disp(SCLK, RCLK, DIO);
unsigned char LED_0F[29];
void setup() {
  Serial.begin(9600);
  pinMode(RELE, OUTPUT);
  digitalWrite(RELE,HIGH);
  pinMode(D2,INPUT);
  setupDisplay();
  disp.send(LED_0F[0], 0b0001);    //send digital "0" to 1st indicator
  delay(2000);
  disp.send(LED_0F[3], 0b0110);    //send digital "3" to 2nd and 3rd indicator
  delay(2000);
  disp.send(LED_0F[10], 0b1111);    //send simbol "A" to all indicators
  delay(2000);
  digitalWrite(RELE,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println (analogRead(D2));
  delay(1000);
}

void setupDisplay() {
  LED_0F[0] = 0xC0; //0
  LED_0F[1] = 0xF9; //1
  LED_0F[2] = 0xA4; //2
  LED_0F[3] = 0xB0; //3
  LED_0F[4] = 0x99; //4
  LED_0F[5] = 0x92; //5
  LED_0F[6] = 0x82; //6
  LED_0F[7] = 0xF8; //7
  LED_0F[8] = 0x80; //8
  LED_0F[9] = 0x90; //9
  LED_0F[10] = 0x88; //A
  LED_0F[11] = 0x83; //b
  LED_0F[12] = 0xC6; //C
  LED_0F[13] = 0xA1; //d
  LED_0F[14] = 0x86; //E
  LED_0F[15] = 0x8E; //F
  LED_0F[16] = 0xC2; //G
  LED_0F[17] = 0x89; //H
  LED_0F[18] = 0xF9; //I
  LED_0F[19] = 0xF1; //J
  LED_0F[20] = 0xC3; //L
  LED_0F[21] = 0xA9; //n
  LED_0F[22] = 0xC0; //O
  LED_0F[23] = 0x8C; //P
  LED_0F[24] = 0x98; //q
  LED_0F[25] = 0x92; //S
  LED_0F[26] = 0xC1; //U
  LED_0F[27] = 0x91; //Y
  LED_0F[28] = 0xFE; //hight -

}
