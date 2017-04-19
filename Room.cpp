#include "Room.h"

void Room::byteToBoolArray(bool dest[8], byte source) {
  for (int i = 0; i < 8; i++) {
    dest[i] = bitRead(source, 7 - i);
  }
}

byte Room::boolArrayToByte (bool source[8]) {
  byte value;
  int targetBit;
  for (int i = 0; i < 8; i++) {
    targetBit = 7 - i;
    bitWrite(value, targetBit, source[i]);
  }

  return value;
}

Room::Room (const byte source[8]) {
  loadRoom(source);
}

Room::Room (const bool source[8][8]) {
  if (source != NULL) {
    memcpy (roomMap, source, sizeof(bool) * 64);
  }
}

void Room::loadRoom (const byte source[8]) {
  if (source != NULL) {
    for (int i = 0; i < 8; i++) {
      byteToBoolArray(roomMap[i], source[i]);
    }
  }
}

void Room::loadRoom (const bool source[8][8]) {
  if (source != NULL) {
    memcpy (roomMap, source, sizeof(bool) * 64);
  }
}

void Room::getRoomByteArray(byte dest[8]) {
  for (int i = 0; i < 8; i++) {
    dest[i] = boolArrayToByte(roomMap[i]);
  }
}

bool Room::checkIfFree (int row, int column) {
  // we don't check outside the room  
	if (row < 0 || column < 0)
		return 1;
	if (row > 7 || column > 7)
		return 1;
  if (roomMap != 0)
    return !roomMap[row][column];
    
  return 0;
}

void Room::printRoomMap() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Serial.print(roomMap[i][j]);
      Serial.print(" ");
    }
    Serial.println("");
  }
  Serial.print("\n\n\n");
}

