#include "Room.h"

void Room::byteToBoolArray(bool dest[8], byte source) {
  for (int i = 0; i < 8; i++) {
    dest[i] = bitRead(source, 7 - i);
  }
}

Room::Room (byte source[8]) {
  loadRoom(source);
}

Room::Room (bool source[8][8]) {
  if (source != NULL) {
    memcpy (roomMap, source, sizeof(bool) * 64);
  }
}

void Room::loadRoom (byte source[8]) {
  if (source != NULL) {
    for (int i = 0; i < 8; i++) {
      byteToBoolArray(roomMap[i], source[i]);
    }
  }
}

void Room::loadRoom (bool source[8][8]) {
  if (source != NULL) {
    memcpy (roomMap, source, sizeof(bool) * 64);
  }
}

bool Room::checkIfFree (int row, int column) {
  return !roomMap[row][column];
}

