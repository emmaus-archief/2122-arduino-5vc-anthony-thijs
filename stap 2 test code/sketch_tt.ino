#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int knopPin1 = 12;
int knopPin2 = 10;
int knopPin3 = 8;
int knopPin4 = 6;
int x = 0;
int y = 1;
int toestand = 1;

const int STIL_STAAND = 1;
const int VOOR_UIT = 2;
const int ACHTER_UIT = 3;

  /*switchState1 = digitalRead(knopPin1);
  switchState2 = digitalRead(knopPin2);
  switchState3 = digitalRead(knopPin3);
  switchState4 = digitalRead(knopPin4); */
  
void setup() {
  
  pinMode(knopPin1, INPUT);
  pinMode(knopPin2, INPUT);
  pinMode(knopPin3, INPUT);
  pinMode(knopPin4, INPUT);
  // kolommen en rijen opzetten van lcd:
  lcd.begin(16, 2);
}

void loop() {

  // put your main code here, to run repeatedly:
 // letter instellen op 1e kolom en rij
  lcd.setCursor (x,y);
  //letter v printen op lcd als "speler"
   lcd.print("v");
   
  if (toestand == STIL_STAAND) { 
    lcd.setCursor (x,y);
    if (digitalRead(knopPin1) == HIGH) {
    toestand = VOOR_UIT;
    lcd.setCursor (x+1,y);
    lcd.print("v");
    }
  }
    if (toestand == VOOR_UIT) { 
        lcd.setCursor (x,y);
    if (digitalRead(knopPin2) == HIGH) {
    toestand = ACHTER_UIT;
    lcd.setCursor (x,y+1);
    lcd.print("v");
    }
 }
}
