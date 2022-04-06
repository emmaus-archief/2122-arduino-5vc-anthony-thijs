#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int knopPin1 = 12;
int knopPin2 = 10;
int knopPin3 = 8;
int knopPin4 = 6;
int toestand = 1;
const int t_knop1 = 1;
const int t_knop2 = 2;
const int t_knop3 = 3;
const int t_knop4 = 4;
int x = 0;
int y = 1;

void setup() {
  
  pinMode(knopPin1, INPUT);
  pinMode(knopPin2, INPUT);
  pinMode(knopPin3, INPUT);
  pinMode(knopPin4, INPUT);
  // kolommen en rijen opzetten van lcd:
  lcd.begin(16, 2);

}

void loop() {
  // letter instellen op 1e kolom en rij
  lcd.setCursor (x,y);
  //letter v printen op lcd als "speler"
  lcd.print("V");  
  
  
  // omhoog
  if (toestand == t_knop1) {
    if (digitalRead(knopPin1) == HIGH) {
    y = y - 1;
      }
    }

  // omlaag
  if (toestand == t_knop2) {
    if(digitalRead(knopPin2) == HIGH) {
    y = y + 1;
        }
     }

  // voor
  if (toestand == t_knop3) {
    if(digitalRead(knopPin3) == HIGH) {
    x = x + 1;
        }
     }

   // achter
  if (toestand == t_knop4) {
    if(digitalRead(knopPin4) == HIGH) {
    x = x - 1;
        }
     }
}
