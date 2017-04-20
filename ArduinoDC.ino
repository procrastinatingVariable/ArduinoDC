#include "Controler.h"
#include "ScreenBuffer.h"
#include "Dungeon.h"

#include <MemoryFree.h>
#include <LedControl.h>


#define CLOCK_PIN 9
#define LOAD_PIN 8
#define DATA_IN_PIN 10

#define LEFT_BUTTON_PIN 6
#define RIGHT_BUTTON_PIN 7
#define UP_BUTTON_PIN 4
#define DOWN_BUTTON_PIN 5
#define ACTION_BUTTON_PIN 3



LedControl lc = LedControl(DATA_IN_PIN, CLOCK_PIN, LOAD_PIN, 1);

Dungeon* d;
Player* p;
Controler c(LEFT_BUTTON_PIN, RIGHT_BUTTON_PIN, UP_BUTTON_PIN, DOWN_BUTTON_PIN, ACTION_BUTTON_PIN);
ScreenBuffer b;



void setup() {
  Serial.begin(9600);
  
  lc.shutdown(0, false);
  lc.setIntensity(0, 10);
  lc.clearDisplay(0);

  Serial.println(2048 - freeMemory());

  d = new Dungeon(dungeon1);

  Serial.println(2048 - freeMemory());

  d->loadDungeon(dungeon2);

  Serial.println(2048 - freeMemory());
  
  p = d->getPlayer();

}


void loop() {
  c.readButtons();

  movePlayer();

  drawRoom();
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

  int pRow = p->getRowRelative();
  int pCol = p->getColumnRelative();
  if (c.getActionState() == Controler::BUTTON_PRESSED) {
    if (currentRoom.hasChest()) {
      if (currentRoom.isNearChest(pRow, pCol)) {
        currentRoom.removeChest();
        debugS += currentRoomNumber;
        Serial.println(debugS);
      }
    }

    if (currentRoom.isInGate (pRow, pCol)) {
      Serial.println("Player is in the gate!");
    }
  }
}

void drawRoom() {
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

