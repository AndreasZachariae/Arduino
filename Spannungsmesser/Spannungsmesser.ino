//www.elegoo.com
//2016.12.9

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0; // Widerstandswert R1 (100K) - siehe Schaltskizze!
float R2 = 10000.0; // Widerstandswert R2 (10K) - siehe Schaltskizze!
float i = 0.0;
int values = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Spannung");
  
  Serial.begin(9600); //Seriellen Monitor einbinden
  pinMode(analogInput, INPUT);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);

  // Werte am analogen Pin lesen
  values = analogRead(analogInput); //Messwerte am analogen Pin als "values" definieren
  vout = (values * 5.0) / 1024.0; // Messwerte in Volt umrechnen = Spannung am Ausgang des
  // Spannungsteilers mit Zuleitung zu Pin A0
  vin = vout / (R2 / (R1 + R2)); // Berechnen, welche Spannung am Eingang des Spannungsteilers anliegt. Das entspricht der Spannung der zu untersuchenden Batterie
  if (vin < 0.09) {
  vin = 0.0; // Unterdrücken unerwünschter Anzeigen
  }
  //i=(vin/(R1+R2))*1000;
  lcd.setCursor(0, 1);
  lcd.print("U = ");
  lcd.print(vin);
  lcd.print("V");
  lcd.setCursor(0, 0);
  lcd.print("Turbinenspannung");
  //lcd.print(i);
  //lcd.print("A");
  delay(500);
  if (vin>=10) {
    lcd.clear();
  }
  Serial.print("V= ");
  Serial.println(vout); // Messwerte am anologen Pin im seriellen Monitor anzeigen
}

