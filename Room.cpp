#include <avr/pgmspace.h>

#include "Room.h"

const int Room::CHEST_WIDTH = 2;
const int Room::CHEST_HEIGHT = 2;

void Room::byteToBoolArray(bool dest[8], byte source) {
	if (dest != 0 && source != 0) {
		for (int i = 0; i < 8; i++) {
			dest[i] = bitRead(source, 7 - i);
		}
	}

}

byte Room::boolArrayToByte (bool source[8]) {
	if (source != NULL) {
		byte value;
		int targetBit;
		for (int i = 0; i < 8; i++) {
			targetBit = 7 - i;
			bitWrite(value, targetBit, source[i]);
		}

		return value;
	}

}

bool Room::isInRoom (int row, int column) {
	if (row < 0 || row > 7) return 0;
	if (column < 0 || column > 7) return 0;
	return 1;
}

void Room::copyBoolMatrix (byte dest[8], bool source[8][8]) {
	if (source != NULL) {
		for (int i = 0; i < 8; i++) {
			dest[i] = boolArrayToByte(source[i]);
		}
	}

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
		memcpy (roomMap, source, sizeof(byte) * 8);
	}
}

void Room::loadRoom (const bool source[8][8]) {
	if (source != NULL) {
		for (int i = 0; i < 8; i++) {
			roomMap[i] = boolArrayToByte(source[i]);
		}

	}
}

#else

void Room::loadRoom (const byte source[8]) {
  if (source != NULL) {
    memcpy_P (roomMap, source, sizeof(byte) * 8);
  }
}

void Room::loadRoom (const bool source[8][8]) {
  if (source != NULL) {
		// we bring the array to RAM
		bool cpy[8][8];
		memcpy_P (cpy, source, sizeof(bool) * 64);

		for (int i = 0; i < 8; i++) {
			roomMap[i] = boolArrayToByte(cpy[i]);
		}

  }
}

#endif

byte* Room::getRoomByteArray() {
	return roomMap;
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
				bitSet(roomMap[i], 7 - j);
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
      bitClear(roomMap[i], 7 - j);
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
  byte gateMask[] = { B00000000,
                    B00000000,
                    B00111100,
                    B00100100,
                    B00100100,
                    B00000000,
                    B00000000,
                    B00000000 };
  int gateTRow = 2;
  int gateTCol = 2;
  int gateWidth = 4;
  int gateHeight = 3;
  int gateBRow = gateTRow + gateHeight - 1;
  int gateBCol = gateTCol + gateWidth - 1;

  if (checkIfFree(gateTRow, gateTCol, gateBRow, gateBCol)) {
    for (int i = 0; i < 8; i++) {
      roomMap[i] |= gateMask[i];
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
  if (roomMap != 0) {
    byte rowByte = roomMap[row];
    return !bitRead(rowByte, 7 - column);
  }
    
  return 0;
}

bool Room::checkIfFree(int tRow, int tColumn,
											 int bRow, int bColumn) {
	if (!isInRoom(tRow, tColumn) || !isInRoom(bRow, bColumn)) {
		return 0;
	}

  
	byte areaMask[] = {0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = tRow; i <= bRow; i++) {
		for (int j = bColumn; j >= tColumn; j--) {
		  bitSet(areaMask[i], 7 - j);
		}

	}

	int sum = 0;
	for (int i = tRow; i <= bRow; i++) {
		byte rowCut = roomMap[i] & areaMask[i];
		sum += rowCut;
	}

	return !sum;
}



void Room::printRoomMap() {
  bool bitValue;
  Serial.print("\n\n");
  for (int i = 0;i < 8; i++) {
    for (int j = 7; j >= 0; j--) {
      bitValue = bitRead(roomMap[i], j);
      Serial.print(bitValue);
      Serial.print(" ");
    }
    Serial.println("");
  }
  Serial.print("\n\n");
}

void Room::debug() {
 
  
}


