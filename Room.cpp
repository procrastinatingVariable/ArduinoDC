#include <avr/pgmspace.h>

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



Room::Room() {
	chestRow = -1;
	chestColumn = -1;
  gatePresent = 0;
}

Room::Room (const byte source[8]) : Room() {
  loadRoom(source);
}

Room::Room (const bool source[8][8]) : Room() {
	loadRoom(source);
}

#ifndef LOAD_FLASH

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

#else

void Room::loadRoom (const byte source[8]) {
  if (source != NULL) {
    // bring the array to RAM
    byte cpy[8];
    memcpy_P (cpy, source, sizeof(byte) * 8);
    
    for (int i = 0; i < 8; i++) {
      byteToBoolArray(roomMap[i], cpy[i]);
    }
  }
}

void Room::loadRoom (const bool source[8][8]) {
  if (source != NULL) {
    memcpy_P (roomMap, source, sizeof(bool) * 64);
  }
}

#endif

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

		chestRow = tRow;
		chestColumn = tColumn;

		for (int i = tRow; i <= bRow; i++) {
			for (int j = tColumn; j <= bColumn; j++) {
				roomMap[i][j] = 1;
			}
		}

	}
}

void Room::removeChest() {
  if (!hasChest())
    return;
  
	int bRow = chestRow + CHEST_HEIGHT - 1;
	int bColumn = chestColumn + CHEST_WIDTH - 1;

	for (int i = chestRow; i <= bRow; i++) {
		for (int j = chestColumn; j <= bColumn; j++) {
			roomMap[i][j] = 0;
		}
	}

  // mark the absence of the chest
  chestRow = -1;
  chestColumn = -1;

}

bool Room::hasChest() {
	if (chestRow == -1 || chestColumn == -1)
    return 0;

  return 1;
}

bool Room::isNearChest (int row, int column) {
  if (!hasChest()) return 0;

  int chestAreaTopRow = chestRow - 1;
  int chestAreaTopCol = chestColumn - 1;
  int chestAreaBotRow = chestAreaTopRow + CHEST_HEIGHT + 1;
  int chestAreaBotCol = chestAreaTopCol + CHEST_WIDTH + 1;

  return (row >= chestAreaTopRow && row <= chestAreaBotRow &&
          column >= chestAreaTopCol && column <= chestAreaBotCol) ;
}



bool Room::addGateway() {
	int gateWidth = 4;
	int gateHeight = 3;
	int gateTopRow = 2;
	int gateTopCol = 2;
	int gateBotRow = gateTopRow + gateHeight - 1;
	int gateBotCol = gateTopCol + gateWidth - 1;
	
	if (checkIfFree(gateTopRow, gateTopCol, gateBotRow, gateBotCol)) {
		for (int i = gateTopRow; i <= gateBotRow; i++) {
			roomMap[i][gateTopCol] = 1;
			roomMap[i][gateBotCol] = 1;
		}
		for (int i = gateTopCol; i <= gateBotCol; i++) {
			roomMap[gateTopRow][i] = 1;
		}

    gatePresent = 1;
	}
}

bool Room::isInGate (int row, int column) {
  if (!gatePresent) return 0;
  // the gate's interior is a fixed 2x2 square
  return (row >= 3 && row <= 4) && (column >= 3 && column <= 4);
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

