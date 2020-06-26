#include "Arduino.h"
#include "MaxMatrix.h"
int led=13;
int DIN = 11;   // DIN pin of MAX7219 module
int CLK = 9;   // CLK pin of MAX7219 module
int CS = 10;    // CS pin of MAX7219 module
int maxInUse = 2;
MaxMatrix m(DIN, CS, CLK, maxInUse); 
char A[] = {4, 8,
            B01111110,
            B00010001,
            B00010001,
            B01111110,
           };
char B[] = {4, 8,
            B01111111,
            B01001001,
            B01001001,
            B00110110,
           };
char smile01[] = {8, 8,
                  B01111111,
                  B10111111,
                  B11011111,
                  B11101111,
                  B11110111,
                  B11111011,
                  B11111101,
                  B11111110
                 };
char smile02[] = {8, 8,
                  B10101011,
                  B10101011,
                  B10101011,
                  B10101011,
                  B10101011,
                  B10101011,
                  B10101011,
                  B10101011
                 };
char smile03[] = {8, 8,
                  B00000000,
                  B11111111,
                  B00000000,
                  B11111111,
                  B00000000,
                  B11111111,
                  B00000000,
                  B11111111
                 };
void setup() {
  pinMode(led, OUTPUT);
  m.init(); // MAX7219 initialization
  m.setIntensity(8); // initial led matrix intensity, 0-15
}
void loop() {
  // Seting the LEDs On or Off at x,y or row,column position
  /*m.setDot(1,8,true); 
  delay(1000);
  m.setDot(5,1,true);*/
  
  m.clear(); // Clears the display
  for (int i=0; i<16; i++){
    for (int j=0; j<16; j++){
      m.setDot(i,j,true);
      digitalWrite(led,HIGH);
      delay(5);
      digitalWrite(led,LOW);
      delay(5);
    }
  }
  //m.clear();
  // Displaying the character at x,y (upper left corner of the character)  
  /*m.writeSprite(2, 0, A);
  delay(1000);
  m.writeSprite(2, 0, B);
  delay(1000);*/
  /*m.writeSprite(0, 0, smile01);
  delay(1000);
  
  m.writeSprite(0, 0, smile02);
  delay(1000);
  
  m.writeSprite(0, 0, smile03);
  delay(1000);
  
  for (int i=0; i<8; i++){
    m.shiftLeft(false,false);
    delay(300);
  }
  */
  m.clear();
}
