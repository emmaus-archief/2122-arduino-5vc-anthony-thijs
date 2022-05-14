#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int upPin = 12;
int downPin = 10;
int leftPin = 8;
int rightPin = 6;

int playerX = 0;
int playerY = 1;
int boneX = 15;
int boneY = random(0,1);
int beamX = 15;
int beamY = random(0,1);

int x = -1;
int y = -1;
int delX = playerX + x;
int delY = playerY + y;

bool warning = false;
bool beamShot = false;

int loopSwitch = 0;
int pauze = 300;
long boneSnelheid = random(200, 1000);


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

const byte beamParticle[8] = {
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111,
  0b11111
};

void beam(){
    for(int beamX = 15; beamX < 16; beamX--){
    if(beamX > 0 && beamY == 0){  
    lcd.createChar(3, beamParticle);//maakt bot obstakel
    lcd.setCursor(beamX, beamY);//plek van obstakel
    lcd.write((byte)3);//print bot
    delay(100);
      }
    }
  }

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
     delay(10);
     lcd.clear();
     y = y + 1;
     lcd.setCursor(delX, delY);
     lcd.print(" ");
     delay(50);    
    }
    }

  if (digitalRead(downPin) == HIGH) {
    knopStatus = tDown;
  if(knopStatus == tDown){
     lcd.createChar(1, player);//maakt speler
     lcd.setCursor(playerX, playerY);//plek van speler
     lcd.write((byte)1);//print speler
     playerY = playerY + 1;
     delay(10);
     lcd.clear();
     y = y - 1;
     lcd.setCursor(delX, delY);
     lcd.print(" ");
     delay(50);
    }
    }  

  if (digitalRead(leftPin) == HIGH) {
      knopStatus = tLeft;
    if(knopStatus == tLeft){
     lcd.createChar(1, player);//maakt speler
     lcd.setCursor(playerX, playerY);//plek van speler
     lcd.write((byte)1);//print speler
     playerX = playerX - 1;
     delay(10);
     lcd.clear();
     x = x + 1;
     lcd.setCursor(delX, delY);
     lcd.print(" ");
     delay(50);
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
     x = x - 1;
     lcd.setCursor(delX, delY);
     lcd.print(" ");
     delay(50);
    }

  }

  //aanvallen
  if(boneX <= 15){ 
    boneX--;
    delay(boneSnelheid);
    lcd.setCursor(boneX + 1, boneY);
    lcd.print(" ");
    }
    
    if(boneX < 0){
      boneX = 15;
      }
    
    if(boneX == 0){
      loopSwitch = loopSwitch + 1;
      }
      
    if(loopSwitch == 1000){
      lcd.setCursor(7,0);
      lcd.print("!!!");
      warning = true;
      }
    if(warning == true){
      beam();
      beamShot = true;
      warning = false;
    }  
    if(beamShot == true){
      int tijd = millis();
      if(tijd == 1000){
        for(int i = 15; i < 16; i--){
         if(i > 0){ 
          lcd.setCursor(i, beamY);
          lcd.print(" ");
            }
          }
        }
      beamShot = false;  
      }
      
    


  if (playerX == boneX && playerY == boneY || playerX == beamX && playerY == beamY){
        gameStatus = GAMEOVER1;
    }  
  }      

  if (gameStatus == GAMEOVER1){
    lcd.clear();
    playerX = 0;
    playerY = 1;
    lcd.setCursor (0,1);
    lcd.print("GAMEOVER");
    }

  if (gameStatus == GAMEOVER1){ 
    if( digitalRead(leftPin)== HIGH){
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
