#include "Room.h"

const int Room::CHEST_WIDTH = 2;
const int Room::CHEST_HEIGHT = 2;

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

bool Room::isInRoom (int row, int column) {
	if (row < 0 || row > 7) return 0;
	if (column < 0 || column > 7) return 0;
	return 1;
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

bool Room::addChest() {
	// a chest is a 2x2 block
	int tRow = 3;
	int tColumn = 3;

	addChest(tRow, tColumn);
}

bool Room::addChest (int tRow, int tColumn) {
	int bRow = tRow + CHEST_HEIGHT - 1;
	int bColumn = tColumn + CHEST_HEIGHT - 1;
	if (checkIfFree(tRow, tColumn,
									bRow, bColumn)) {
		for (int i = tRow; i <= bRow; i++) {
			for (int j = tColumn; j <= bColumn; j++) {
				roomMap[i][j] = 1;
			}
		}
	}
}

bool Room::checkIfFree (int row, int column) {
  // we don't check outside the room  
	if (!isInRoom(row, column))
		return 1;
  if (roomMap != 0)
    return !roomMap[row][column];
    
  return 0;
}

bool Room::checkIfFree(int tRow, int tColumn,
											 int bRow, int bColumn) {
	if (!isInRoom(tRow, tColumn) || !isInRoom(bRow, bColumn)) {
		return 0;
	}

	int sum = 0;
	for (int i = tRow; i <= tColumn; i++) {
		for (int j = bRow; j <= bColumn; j++) {
			sum += roomMap[i][j];
		}
	}

	return !sum;
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

