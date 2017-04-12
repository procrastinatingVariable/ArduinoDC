#include "map.h"
#include <LedControl.h>
#include "Controler.h"
#include "Player.h"
#include "ScreenBuffer.h"

#define CLOCK_PIN 6
#define LOAD_PIN 8
#define DATA_IN_PIN 7

#define LEFT_BUTTON_PIN 11
#define RIGHT_BUTTON_PIN 10
#define UP_BUTTON_PIN 9
#define DOWN_BUTTON_PIN 12

Player p;
Controler c;
ScreenBuffer b;

LedControl lc = LedControl(DATA_IN_PIN, CLOCK_PIN, LOAD_PIN, 1);

void setup() {
  Serial.begin(9600);
  
  lc.shutdown(0, false);
  lc.setIntensity(0, 10);
  lc.clearDisplay(0);

  p = Player(6, 1);
  c = Controler(LEFT_BUTTON_PIN, RIGHT_BUTTON_PIN, UP_BUTTON_PIN, DOWN_BUTTON_PIN);
  b = ScreenBuffer();
}

int currentScreenNumber = 0;
void loop() {
  lc.clearDisplay(0);
  c.readButtons();

  Serial.print(p.getRow());
  Serial.print(" ");
  Serial.println(p.getColumn());

  if (c.getLeftState() == Controler::BUTTON_PRESSED) {
    p.moveLeft();
  } else if (c.getRightState() == Controler::BUTTON_PRESSED) {
    p.moveRight();
  } else if (c.getUpState() == Controler::BUTTON_PRESSED) {
    p.moveUp();
  } else if (c.getDownState() == Controler::BUTTON_PRESSED) {
    p.moveDown();
  }
  getRoom(0);
  displayPlayer();
  b.drawBuffer(lc, 0);

  delay(150);
}

void getRoom(int roomNumber) {
  byte rawRoom[8];
  memcpy(rawRoom, map2 + roomNumber * 8, 8);

  b.loadBuffer(rawRoom);
}

void displayPlayer() {
  int playerRow = p.getRow();
  int playerColumn = p.getColumn();
  b.writeToBuffer(playerRow, playerColumn, 1);
}

