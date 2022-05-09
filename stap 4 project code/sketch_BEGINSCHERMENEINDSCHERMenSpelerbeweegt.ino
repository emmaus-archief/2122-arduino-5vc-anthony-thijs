#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;


const int Beginscherm = 0;
const int Spelen = 3;
const int Gameover = 4;
const int Starten = 2;
const int Regeltjes = 1;
int toestand = Starten;

/*
int tUp = 1;
int tDown = 2;
int tLeft = 3;
int tRight = 4;
8*/

int upPin = 12;
int downPin = 10;
int leftPin = 8;
int rightPin = 6;

int knopupPin = LOW;
int knopdownPin = LOW;
int knopleftPin = LOW;
int knoprightPin = LOW;

int playerX = 0;
int playerY = 1;
int boneX = 13;
int boneY = 1;

int pauze = 250;

int printT = false;

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
  // put your setup code here, to run once:
pinMode(upPin, INPUT);
  digitalWrite(upPin, HIGH);
  pinMode(downPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  lcd.setCursor(0,0);
  lcd.print("Druk gele");
  lcd.setCursor(0, 1);
  lcd.print("Knop voor regeltjes");

}
void loop() {
  // put your main code here, to run repeatedly:
  toestand = Starten; 
  knopupPin = digitalRead(upPin);
  knopdownPin = digitalRead(downPin);
  knopleftPin = digitalRead(leftPin);
  knoprightPin = digitalRead(rightPin);

  if (toestand == Starten & knopdownPin == HIGH) {
    toestand = Regeltjes;
  }
  if (toestand == Regeltjes) {
 lcd.setCursor(0,0);
    lcd.print("Druk blauwe");
    lcd.setCursor(0, 1);
    lcd.print("Knop voor omhoog");
    if (knopdownPin == HIGH) {
      toestand = Beginscherm;
    }
  }
 if (toestand == Regeltjes & knopdownPin == HIGH) {
  toestand = Beginscherm;
 }
  
  if (toestand == Beginscherm) {
    lcd.setCursor(0,0);
    lcd.print("Druk gele");
    lcd.setCursor(0, 1);
    lcd.print("Knop voor starten");
    if (knopdownPin == HIGH) {
      toestand = Spelen;
    }
  }

  if( toestand == Spelen) { 
  lcd.createChar(1, player);//maakt speler
  lcd.setCursor(playerX, playerY);//plek van speler
  lcd.write((byte)1);//print speler

  lcd.createChar(2, bone);//maakt bot obstakel
  lcd.setCursor(boneX, boneY);//plek van obstakel
  lcd.write((byte)2);//print bot

  if (knopdownPin == HIGH && playerY >=0){
      playerY = playerY - 1;
      delay(200);
  }
  if (knopupPin == HIGH && playerY >= 0) {
    playerY = playerY + 1;
    delay(200);
  }
  if(knopleftPin == HIGH && playerX > 0) {
    playerX = playerX - 1;
    delay(200);
  }
  if(knoprightPin == HIGH && playerX > 0) {
    playerX = playerX + 1;
    delay(200);
  }


 if (toestand== Gameover) {
    lcd.setCursor(0, 1);
    lcd.print("Game Over");
 if (knopdownPin == HIGH) {
      toestand = Beginscherm;
      
    }
  }
  }
}
