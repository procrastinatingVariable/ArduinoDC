#include "Dungeon.h"

int Dungeon::dungeonInstances = 0;

int Dungeon::computeDungeonMapSize() {
  return dungeonWidth * dungeonHeight * 8;
}

void Dungeon::loadRooms(const byte* dungeonMap) {
  int numberOfRooms = getRoomNumber();

  // clear out the currently loaded map
  if (dungeonRooms != 0) {
    freeRoomMemory();
  }
  
  dungeonRooms = new Room*[numberOfRooms];
  Serial.print("Pointer after creation : ");
  Serial.println((int)dungeonRooms, HEX);
  for (int i = 0; i < numberOfRooms; i++) {
    int roomOffset = i * 8;
    const byte* roomStartPointer = dungeonMap + roomOffset;
    dungeonRooms[i] = new Room(roomStartPointer);
  }
}

Dungeon::Dungeon() {
  // singleton class
  if (dungeonInstances == 1) return;

  this->avatar = new Player();
  this->dungeonRooms = 0;

  dungeonInstances = 1;
}

Dungeon::Dungeon(const Level& startMap) : Dungeon(){
  loadDungeon(startMap);
}


void Dungeon::loadDungeon (const Level& dungeon) {
  // load the rooms
  dungeonWidth = dungeon.width;
  dungeonHeight = dungeon.height;

  loadRooms(dungeon.dungeonMap);

  // initialize player position
  int playerStartingRow = 2;
  int playerStartingColumn = 2;
  placePlayer(dungeon.startRoom, playerStartingRow, playerStartingColumn);
}

Player* Dungeon::getPlayer() {
  return avatar;
}

int Dungeon::getPlayerRoomNumber() {
  int roomGridRowIndex = floor(avatar->getRowAbsolute() / 8);
  int roomGridColumnIndex = floor(avatar->getColumnAbsolute() / 8);

  return roomGridRowIndex * dungeonWidth + roomGridColumnIndex;
  
}

int Dungeon::getRoomNumber() {
  return dungeonWidth * dungeonHeight;
}

Room& Dungeon::getRoom (int number) {
  int numberOfRooms = getRoomNumber();
  if (number >= 0 && number < numberOfRooms) {
    return *dungeonRooms[number];
  }
}

Room& Dungeon::getRoom (int row, int column) {
  if (row < dungeonHeight && column < dungeonWidth) {
    int roomNumber = row * dungeonWidth + column;
    return getRoom(roomNumber);
  }
}

bool Dungeon::placePlayer (int roomNumber, int playerRow, int playerCol) {
  int numberOfRooms = getRoomNumber();
  if (roomNumber < 0 || roomNumber >= numberOfRooms) return 0;
  
  int roomGridRowIndex = floor(roomNumber / dungeonWidth);
  int roomGridColumnIndex = roomNumber - roomGridRowIndex * dungeonWidth;

  return placePlayer(roomGridRowIndex, roomGridColumnIndex, playerRow, playerCol);
}

bool Dungeon::placePlayer (int roomRowIndex, int roomColIndex, int playerRow, int playerCol) {
  if (roomRowIndex < 0 || roomRowIndex >= dungeonHeight) return 0;
  if (roomColIndex < 0 || roomColIndex >= dungeonWidth) return 0;
  
  int roomWidth = 8;
  int roomHeight = 8;
  if (playerRow < 0 || playerRow >= roomHeight) return 0;
  if (playerCol < 0 || playerCol >= roomWidth) return 0;

  int playerAbsoluteRow = roomRowIndex * roomHeight + playerRow;
  int playerAbsoluteCol = roomColIndex * roomWidth + playerCol;

  avatar->setRowAbsolute(playerAbsoluteRow);
  avatar->setColumnAbsolute(playerAbsoluteCol);

  return 1;
}


void Dungeon::freeRoomMemory() {
  for (int i = 0; i < getRoomNumber(); i++) {
    delete dungeonRooms[i];
  }
  delete[] dungeonRooms;
}



Dungeon::~Dungeon() {
  for (int i = 0;i < getRoomNumber(); i++) {
    delete dungeonRooms[i];
  }
  delete[] dungeonRooms;
  delete avatar;
  dungeonInstances = 0;
}

