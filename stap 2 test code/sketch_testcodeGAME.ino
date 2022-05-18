#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int upPin = 12;
int downPin = 10;
int leftPin = 8;
int rightPin = 6;


int playerX = 0;
int playerY = 1;
int boneX = 13;
int boneY = 1;


int toestand = 1;
const int tUp = 1;
const int tDown = 2;
const int tLeft = 3;
const int tRight = 4;

//characters(obstacle/player)
const byte player[8] = {
  0b00000,
  0b00000,
  0b11011,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

const byte bone[8] = {
  0b11011,
  0b01110,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b01110,
  0b11011
};


void setup() {
  pinMode(upPin, INPUT);
  digitalWrite(upPin, HIGH);
  pinMode(downPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  lcd.begin(16, 2)//startplek
  lcd.createChar(1, player);//maakt speler
  lcd.setCursor(playerX, playerY);//plek van speler
  lcd.write((byte)1);//print speler
  lcd.createChar(2, bone);//maakt bot obstakel
  lcd.setCursor(boneX, boneY);//plek van obstakel
  lcd.write((byte)2);//print bot
  
}

void loop() {
  

  if (digitalRead(upPin)== HIGH) {
    toestand = tUp;
    if(toestand == tUp){
     lcd.print ("1");    
    }
    }
  if (digitalRead(downPin) == HIGH) {
    toestand = tDown;
    if(toestand == tDown){
     lcd.print ("2");
    }
    }  
  if (digitalRead(leftPin) == HIGH) {
    toestand = tLeft;
    if(toestand == tLeft){
     lcd.print ("3");
    }
    }

  if (digitalRead(rightPin) == HIGH) {
    toestand = tRight;
    if(toestand == tRight){
     lcd.print ("4");
    }
  }
}
