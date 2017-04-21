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

#define NUM_OF_KEYS 3



LedControl lc = LedControl(DATA_IN_PIN, CLOCK_PIN, LOAD_PIN, 1);

Dungeon* d;
Player* p;
Controler c(LEFT_BUTTON_PIN, RIGHT_BUTTON_PIN, UP_BUTTON_PIN, DOWN_BUTTON_PIN, ACTION_BUTTON_PIN);
ScreenBuffer b;

int currentLevel;
bool gatewayAdded;


void initScreen() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 10);
  lc.clearDisplay(0);

}

void initDungeon() {
  currentLevel = 2;
  d = new Dungeon();
  loadLevel(currentLevel);

  p = d->getPlayer();
  
}

void loadLevel (int levelNum) {
  Serial.println("************************");
  Serial.print("Loaded level : ");
  Serial.println(currentLevel);
  Serial.println("************************");
  
  // reset the number of keys the player has
  p->setKeys(0);
  gatewayAdded = 0;
  
  switch(levelNum) {
    case 1:
      d->loadDungeon(dungeon1);
      break;

    case 2:
      d->loadDungeon(dungeon2);
      break;

    default:
      d->loadDungeon(dungeon1);
  }

  initKeys();
}

void initKeys() {
  randomSeed(analogRead(0));
  int playerStartingRoom = d->getPlayerRoomNumber();
  int numOfRooms = d->getRoomNumber();

  int keyLocations[3];
  for (int i = 0; i < NUM_OF_KEYS; i++) {
    int rRoom;
    // generate numbers untill you found one of a room who's empty (player or chest)
    while ((rRoom = random(0, numOfRooms)) == playerStartingRoom || 
            d->getRoom(rRoom).hasChest()) {}

    d->getRoom(rRoom).addChest();
    Serial.print("Added a chest in room ");
    Serial.println(rRoom);
  }
  
}

void placeGate() {
  randomSeed(analogRead(0));
  int playerCurrentRoom = d->getPlayerRoomNumber();
  int numOfRooms = d->getRoomNumber();

  int rRoom;
  while ((rRoom = random(0, numOfRooms)) == playerCurrentRoom) {}

  d->getRoom(rRoom).addGateway();
  Serial.print("Gateway to next level added to room ");
  Serial.println(rRoom);
}

void setup() {
  Serial.begin(9600);

  initScreen();
  initDungeon();

}






void loop() {
  c.readButtons();

  movePlayer();

  drawRoom();
  displayPlayer();
  doAction();

  if (p->getKeys() == NUM_OF_KEYS && gatewayAdded == 0) {
    placeGate();
    gatewayAdded = 1;
  }

  // change to next dungeon if the player found the gateway
  int currentRoomNum = d->getPlayerRoomNumber();
  if (gatewayAdded) {
    Room& currentRoom = d->getRoom(currentRoomNum);
    int playerRow = p->getRowRelative();
    int playerCol = p->getColumnRelative();
    if (currentRoom.isInGate(playerRow, playerCol)) {
      currentLevel++;
      loadLevel(currentLevel);
    }
  }

  
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
  String debugS = "Player has collected the key in room #";

  int currentRoomNumber = d->getPlayerRoomNumber();
  Room& currentRoom = d->getRoom(currentRoomNumber);

  int pRow = p->getRowRelative();
  int pCol = p->getColumnRelative();
  if (c.getActionState() == Controler::BUTTON_PRESSED) {
    if (currentRoom.hasChest()) {
      if (currentRoom.isNearChest(pRow, pCol)) {
        p->addKey();
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
  byte* roomByteArray;
  int roomNumber = d->getPlayerRoomNumber();
  roomByteArray = d->getRoom(roomNumber).getRoomByteArray();
  b.loadBuffer(roomByteArray);
}

void displayPlayer() {
  int playerRow = p->getRowRelative();
  int playerColumn = p->getColumnRelative();
  b.writeToBuffer(playerRow, playerColumn, 1);
}

