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

int pauze = 300;

int gameStatus = 0;
const int BEGINSCHERM1 = 0;
const int BEGINSCHERM2 = 1;
const int SPELEN = 2;
const int GAMEOVER1 = 3;
const int GAMEOVER2 = 4;

int knopStatus = 1;
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
  lcd.begin(16, 2);
 gameStatus == BEGINSCHERM1;
}

void loop() {
  
  if (gameStatus == BEGINSCHERM1) {
    lcd.print(" Knop 1&2 is ^ v");
    lcd.setCursor(0,1);
    lcd.print(" Knop 3&4 is < >");
    lcd.setCursor(0,0);
    }
  
  if(gameStatus == BEGINSCHERM1){
    if (digitalRead(upPin)== HIGH) {
    lcd.clear();
    lcd.print("Druk knop");
    lcd.setCursor(0,1);
    lcd.print("Geel in");
    lcd.setCursor(0,0);
   gameStatus = BEGINSCHERM2;
   
    }
  }
  
  if (gameStatus == BEGINSCHERM2){ 
    if (digitalRead(downPin)== HIGH){
    lcd.clear();
    gameStatus = SPELEN;
    delay(500);
    }
  }

  if (gameStatus == SPELEN){
    lcd.createChar(1, player);//maakt speler
    lcd.setCursor(playerX, playerY);//plek van speler
    lcd.write((byte)1);//print speler

    
    lcd.createChar(2, bone);//maakt bot obstakel
    lcd.setCursor(boneX, boneY);//plek van obstakel
    lcd.write((byte)2);//print bot

    if (digitalRead(upPin)== HIGH) {
    knopStatus = tUp;
    if(knopStatus == tUp){
      lcd.createChar(1, player);//maakt speler
     lcd.setCursor(playerX, playerY);//plek van speler
     lcd.write((byte)1);//print speler
     playerY = playerY - 1;
     delay(200);    
    }
    }
  
  if (digitalRead(downPin) == HIGH) {
    knopStatus = tDown;
  if(knopStatus == tDown && playerY == 0){
     lcd.createChar(1, player);//maakt speler
     lcd.setCursor(playerX, playerY);//plek van speler
     lcd.write((byte)1);//print speler
     playerY = playerY + 1;
     delay(200);
    }
    }  

      if (digitalRead(leftPin) == HIGH) {
    knopStatus = tLeft;
    if(knopStatus == tLeft && playerX > 0){
     
     lcd.createChar(1, player);//maakt speler
     lcd.setCursor(playerX, playerY);//plek van speler
     lcd.write((byte)1);//print speler
     
     playerX = playerX - 1;
     delay(200);
    }
    }
    
    if (digitalRead(rightPin) == HIGH) {
    knopStatus = tRight;
    if(knopStatus == tRight && playerX < 13){
     lcd.createChar(1, player);//maakt speler
     lcd.setCursor(playerX, playerY);//plek van speler
     lcd.write((byte)1);//print speler
     
     playerX = playerX + 1;
     delay(10);
    }
    
  }
    
    
      if (playerX == boneX && playerY == boneY){
        gameStatus = GAMEOVER1;
        }  
      }      

  if (gameStatus == GAMEOVER1){
    
    lcd.clear();
    lcd.setCursor (0,1);
    lcd.print("GAMEOVER");
    }

  if (gameStatus == GAMEOVER1 && digitalRead(leftPin)== HIGH){
    
    lcd.setCursor(0,1);
    lcd.print("Druk knop");
    lcd.setCursor(0,0);
    lcd.print("Groen in");
    gameStatus = BEGINSCHERM1; 
    }

  
}
