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
int boneX2 = 20;
int boneY = 1;
int boneY2 = 0;

bool bot2 = false;

int pauze = 300;
long boneSnelheid = 200;

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

int score = 0;

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

    lcd.createChar(2, bone);//maakt bot obstakel
    lcd.setCursor(boneX2, boneY2);//plek van obstakel
    lcd.write((byte)2);//print bot

    lcd.setCursor(14, 0);
    lcd.print(score);

    if (digitalRead(upPin)== HIGH) {
    knopStatus = tUp;
    if(knopStatus == tUp && playerY > 0){
      lcd.createChar(1, player);//maakt speler
     lcd.setCursor(playerX, playerY);//plek van speler
     lcd.write((byte)1);//print speler
     playerY = playerY - 1;
     delay(10);
     lcd.clear();
    
    }
    }

  if (digitalRead(downPin) == HIGH) {
    knopStatus = tDown;
  if(knopStatus == tDown && playerY < 2){
     lcd.createChar(1, player);//maakt speler
     lcd.setCursor(playerX, playerY);//plek van speler
     lcd.write((byte)1);//print speler
     playerY = playerY + 1;
     delay(10);
     lcd.clear();
     
    }
    }  

  if (digitalRead(leftPin) == HIGH) {
      knopStatus = tLeft;
    if(knopStatus == tLeft && playerX > 0){
     lcd.createChar(1, player);//maakt speler
     lcd.setCursor(playerX, playerY);//plek van speler
     lcd.write((byte)1);//print speler
     playerX = playerX - 1;
     delay(10);
     lcd.clear();
     
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
     lcd.clear();
    }

  }

  //aanvallen
  if(boneX <= 13){ 
    boneX--;
    delay(boneSnelheid);
    lcd.setCursor(boneX + 1, boneY);
    lcd.print(" ");
    }


    if(boneX < 0){
      boneX = 13;
      score + 1;
      }

    if(boneX2 < 0){
      boneX2 = 13;
      score + 1;
      }

    if(boneX == 1){
      bot2 = true;
      
      }

    if(bot2 == true){
      boneX2--;
      delay(boneSnelheid);
      lcd.setCursor(boneX2 + 1, boneY2);
      lcd.print(" ");
      }

  if (playerX == boneX && playerY == boneY || playerX == boneX2 && playerY == boneY2){
        gameStatus = GAMEOVER1;
    }  
  }      

  if (gameStatus == GAMEOVER1){
    lcd.clear();
    playerX = 0;
    playerY = 1;
    boneX = 13;
    boneX2 = 20;
    lcd.setCursor (4,0);
    lcd.print("GAMEOVER");
    lcd.setCursor (4, 1);
    lcd.print("score:" + score);
    }

  if (gameStatus == GAMEOVER1){ 
    if(digitalRead(leftPin)== HIGH){
    score = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Druk knop");
    lcd.setCursor(0,1);
    lcd.print("Rood in");
    gameStatus = GAMEOVER2; 
    }
  }

  if (gameStatus == GAMEOVER2){ 
    if(digitalRead(rightPin)== HIGH) {
    lcd.clear();
    gameStatus = BEGINSCHERM1;
    delay(500);
    }
  }
}
