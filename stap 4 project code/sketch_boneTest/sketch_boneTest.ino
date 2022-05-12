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
int beamY = random(0,1);

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
    lcd.createChar(2, bone);//maakt bot obstakel
    lcd.setCursor(boneX, boneY);//plek van obstakel
    lcd.write((byte)2);//print bot

    if(boneX <= 15){ 
    boneX--;
    delay(boneSnelheid);
    lcd.setCursor(boneX + 1, boneY);
    lcd.print(" ");
    }

    if(boneX == 0){
      loopSwitch = loopSwitch + 1;
      }
      
    if(loopSwitch == 3){
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
      
    if(boneX < 0){
      boneX = 15;
      }


}
