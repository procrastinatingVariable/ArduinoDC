#include "map.h"
#include <LedControl.h>
#include "Controler.h"
#include "Player.h"
#include "ScreenBuffer.h"
#include "Room.h"
#include "Dungeon.h"

#define CLOCK_PIN 6
#define LOAD_PIN 8
#define DATA_IN_PIN 7

#define LEFT_BUTTON_PIN 11
#define RIGHT_BUTTON_PIN 10
#define UP_BUTTON_PIN 9
#define DOWN_BUTTON_PIN 12

Dungeon* d;
Player* p;
Controler c(LEFT_BUTTON_PIN, RIGHT_BUTTON_PIN, UP_BUTTON_PIN, DOWN_BUTTON_PIN);
ScreenBuffer b;

LedControl lc = LedControl(DATA_IN_PIN, CLOCK_PIN, LOAD_PIN, 1);

void setup() {
  Serial.begin(9600);
  
  lc.shutdown(0, false);
  lc.setIntensity(0, 10);
  lc.clearDisplay(0);

  d = new Dungeon(dungeon1);
  p = d->getPlayer();
}

int currentScreenNumber = 0;
void loop() {
  c.readButtons();



  Serial.print("Absolute : ");
  Serial.print(p->getRowAbsolute());
  Serial.print(" ");
  Serial.println(p->getColumnAbsolute());
  Serial.print("Relative : ");
  Serial.print(p->getRowRelative());
  Serial.print(" ");
  Serial.println(p->getColumnRelative());
  Serial.println("...........................");

  if (c.getLeftState() == Controler::BUTTON_PRESSED) {
    p->moveLeft();
  } else if (c.getRightState() == Controler::BUTTON_PRESSED) {
    p->moveRight();
  } else if (c.getUpState() == Controler::BUTTON_PRESSED) {
    p->moveUp();
  } else if (c.getDownState() == Controler::BUTTON_PRESSED) {
    p->moveDown();
  }
  getRoom();
  displayPlayer();
  b.drawBuffer(lc, 0);

  delay(250);
}

void getRoom() {
  byte roomByteArray[8];
  int roomNumber = d->getPlayerRoomNumber();
  d->getRoom(roomNumber).getRoomByteArray(roomByteArray);
  b.loadBuffer(roomByteArray);
}

void displayPlayer() {
  int playerRow = p->getRowRelative();
  int playerColumn = p->getColumnRelative();
  b.writeToBuffer(playerRow, playerColumn, 1);
}

