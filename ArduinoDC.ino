#include "map.h"
#include <LedControl.h>
#include "Controler.h"
#include "Player.h"
#include "ScreenBuffer.h"
#include "Room.h"
#include "Dungeon.h"

#define CLOCK_PIN 9
#define LOAD_PIN 8
#define DATA_IN_PIN 10

#define LEFT_BUTTON_PIN 6
#define RIGHT_BUTTON_PIN 7
#define UP_BUTTON_PIN 4
#define DOWN_BUTTON_PIN 5
#define ACTION_BUTTON_PIN 3

Dungeon* d;
Player* p;
Controler c(LEFT_BUTTON_PIN, RIGHT_BUTTON_PIN, UP_BUTTON_PIN, DOWN_BUTTON_PIN, ACTION_BUTTON_PIN);
ScreenBuffer b;

LedControl lc = LedControl(DATA_IN_PIN, CLOCK_PIN, LOAD_PIN, 1);

void setup() {
  Serial.begin(9600);
  
  lc.shutdown(0, false);
  lc.setIntensity(0, 10);
  lc.clearDisplay(0);

  d = new Dungeon(dungeon1);
  p = d->getPlayer();


  for (int i = 0; i < d->getRoomNumber(); i+=2) {
    d->getRoom(i).addChest();
  }
}

void loop() {
  c.readButtons();

  movePlayer();

//  Serial.print("Absolute : ");
//  Serial.print(p->getRowAbsolute());
//  Serial.print(" ");
//  Serial.println(p->getColumnAbsolute());
//  Serial.print("Relative : ");
//  Serial.print(p->getRowRelative());
//  Serial.print(" ");
//  Serial.println(p->getColumnRelative());
//  Serial.println("...........................");


  getRoom();
  displayPlayer();
  doAction();
  b.drawBuffer(lc, 0);

  
  delay(150);
}

void movePlayer() {
  int currentRoomNumber = d->getPlayerRoomNumber();
  Room& currentRoom = d->getRoom(currentRoomNumber);
  if (c.getUpState() == Controler::BUTTON_PRESSED) {
    p->move(Player::MOVE_UP, currentRoom);
  } else if (c.getDownState() == Controler::BUTTON_PRESSED) {
    p->move(Player::MOVE_DOWN, currentRoom);
  } else if (c.getLeftState() == Controler::BUTTON_PRESSED) {
    p->move(Player::MOVE_LEFT, currentRoom);
  } else if (c.getRightState() == Controler::BUTTON_PRESSED) {
    p->move(Player::MOVE_RIGHT, currentRoom);
  } 
}

void doAction() {
  String debugS = "Chest has been removed from room #";

  
  int currentRoomNumber = d->getPlayerRoomNumber();
  Room& currentRoom = d->getRoom(currentRoomNumber);
  if (c.getActionState() == Controler::BUTTON_PRESSED) {
    if (currentRoom.hasChest()) {
      currentRoom.removeChest();
      debugS += currentRoomNumber;
      Serial.println(debugS);
    }
  }
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

