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
int boneX2 = 23;
int boneX3 = 24;
const int boneY = 1;
const int boneY2 = 0;
int boneY3 = 0;

bool bot2 = false;
int loopSwitch = 0;
int boneSnelheid = 200;
unsigned long tijd = 0;

int gameStatus = 0;
const int BEGINSCHERM1 = 0;
const int BEGINSCHERM2 = 1;
const int BEGINSCHERM3 = 2;
const int SPELEN = 3;
const int GAMEOVER1 = 4;
const int GAMEOVER2 = 5;
const int GEWONNEN = 6;
const int GEWONNEN2 = 7;

int knopStatus = 1;
const int tUp = 1;
const int tDown = 2;
const int tLeft = 3;
const int tRight = 4;

int score = 0;
int scorePos = 14;
int lives = 20;
int livesPos = 14;

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

const byte star[8] = {
  0b00000,
  0b00100,
  0b10101,
  0b01110,
  0b00100,
  0b01010,
  0b10001,
  0b00000
};

void setup() {
  pinMode(upPin, INPUT);
  digitalWrite(upPin, HIGH);
  pinMode(downPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  lcd.begin(16, 2);
}

void loop() { 

//Beginscherm
  if (gameStatus == BEGINSCHERM1){
    lcd.setCursor(3,0);
    lcd.print("Gl!tchw0r1d");
    lcd.setCursor(2,1);
    lcd.print("Druk op groen");
    lcd.autoscroll();
    delay(1000);
    if(digitalRead(upPin)== HIGH){
      lcd.clear();
      lcd.noAutoscroll();
      gameStatus = BEGINSCHERM2;
      delay(200);
      }
    }
    
  if (gameStatus == BEGINSCHERM2) {
    lcd.print(" Groen&geel: ^ v");
    lcd.setCursor(0,1);
    lcd.print("Wit&rood: < >");
    lcd.setCursor(0,0);
    }

  if(gameStatus == BEGINSCHERM2){
    if (digitalRead(upPin)== HIGH) {
    lcd.clear();
    lcd.print("Druk geel");
    lcd.setCursor(0,1);
    lcd.print("om te starten");
    lcd.setCursor(0,0);
   gameStatus = BEGINSCHERM3;
    }
  }

  if (gameStatus == BEGINSCHERM3){ 
    if (digitalRead(downPin)== HIGH){
    lcd.clear();
    gameStatus = SPELEN;
    delay(500);
    }
  }

//spelen
  if (gameStatus == SPELEN){

    score++;
    
    lcd.createChar(1, player);//maakt speler
    lcd.setCursor(playerX, playerY);//plek van speler
    lcd.write((byte)1);//print speler

    lcd.createChar(2, bone);//maakt bot obstakel
    lcd.setCursor(boneX, boneY);//plek van obstakel
    lcd.write((byte)2);//print bot

    lcd.createChar(2, bone);//maakt bot obstakel
    lcd.setCursor(boneX2, boneY2);//plek van obstakel
    lcd.write((byte)2);//print bot

    lcd.createChar(2, bone);//maakt bot obstakel
    lcd.setCursor(boneX3, boneY3);//plek van obstakel
    lcd.write((byte)2);//print bot

    lcd.setCursor(scorePos, 0);
    lcd.print(score);

    lcd.setCursor(livesPos, 1);
    lcd.print(lives);

    if(score > 99){
      scorePos = 13;
      }

    //beweging speler
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
  if(knopStatus == tDown && playerY < 1){
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

  //obstakels(bot en illusie bot)
  if(boneX <= 13){ 
    boneX--;
    delay(boneSnelheid);
    lcd.setCursor(boneX + 1, boneY);
    lcd.print(" ");
    }

    if(boneX < 0){
      boneX = 13;
      }

    if(boneX2 < 0){
      boneX2 = 13;
      }

    if(boneX3 < 0){
      boneX3 = 13;
      loopSwitch++;
      } 
       
    if(loopSwitch == 2 && boneY3 == boneY2){
      boneY3 = boneY;
      boneX3 = boneX + 13;
      loopSwitch = 0;
      }
    if(loopSwitch == 2 && boneY3 == boneY){
      boneY3 = boneY2;
      loopSwitch = 0;
      }

    if(boneX == 1){
      bot2 = true;
      }  

    if(bot2 == true){
      boneX2--;
      boneX3--;
      if(boneY3 == boneY2){
      lcd.setCursor(boneX3 + 1, boneY3);
      lcd.print(" ");  
        }
      if(boneY3 == boneY){
      lcd.setCursor(boneX3 + 1, boneY3);
      lcd.print(" ");
      lcd.setCursor(boneX2 + 1, boneY2);
      lcd.print(" ");
        }
      }

//schade
  if(playerX == boneX && playerY == boneY || playerX == boneX2 && playerY == boneY2 || playerX == boneX3 && playerY == boneY3){
    lives--;
    }      

//win,verlies conditie
  if (lives == 0){
        lcd.clear();
        gameStatus = GAMEOVER1;
    }   
  }

  if (playerX == 13){
    gameStatus = GEWONNEN;
    }

  if (gameStatus == GEWONNEN){
    playerX = 0;
    playerY = 1;
    boneX = 13;
    boneX2 = 20;
    lcd.setCursor(3,0);
    lcd.print("YOU WON");
    }  

  if (gameStatus == GEWONNEN){
    if(digitalRead(upPin) == HIGH){
      lcd.clear();
      gameStatus = GEWONNEN2;
      }    
    }

  if (gameStatus == GEWONNEN2){
    lcd.setCursor (4, 0);
      lcd.print("score:");
      lcd.setCursor (10,0);
      lcd.print(score);
      if(score > 299){
        for(int i = 0; i < 4; i++){
          lcd.createChar(3, star);
          lcd.setCursor(1 + i, 1);
          lcd.write((byte)3);
          }
      lcd.setCursor (5,1);
      lcd.print("Legendary");  
        }
      if(score > 199 && score < 300){
        for(int i = 0; i < 3; i++){
          lcd.createChar(3, star);
          lcd.setCursor(1 + i, 1);
          lcd.write((byte)3);
        }
      lcd.setCursor (5,1);
      lcd.print("Epic"); 
      } 
      if(score > 50 && score < 200){
        for(int i = 0; i < 2; i++){
          lcd.createChar(3, star);
          lcd.setCursor(i, 1);
          lcd.write((byte)3);
        }
      lcd.setCursor (5,1);
      lcd.print("Cool"); 
    }
      
  if (gameStatus == GEWONNEN2){ 
    if(digitalRead(rightPin)== HIGH) {
    lcd.clear();
    gameStatus = BEGINSCHERM2;
    delay(500);
    }
  }  

  if (gameStatus == GAMEOVER1){
    playerX = 0;
    playerY = 1;
    boneX = 13;
    boneX2 = 23;
    boneX3 = 24;
    lcd.setCursor (4,0);
    lcd.print("get dunked on");
    lcd.setCursor (2, 1);
    lcd.print("score:");
    lcd.setCursor (10,1);
    lcd.print(score);
    }

  if (gameStatus == GAMEOVER1){ 
    if(digitalRead(upPin)== HIGH){
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
    gameStatus = BEGINSCHERM2;
    delay(500);
    }
  }
}
}
