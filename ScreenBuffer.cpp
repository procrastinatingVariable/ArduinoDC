#include "ScreenBuffer.h"


byte ScreenBuffer::boolArrayToByte (bool source[8]) {
  byte value;
  int targetBit;
  for (int i = 0; i < 8; i++) {
    targetBit = 7 - i;
    bitWrite(value, targetBit, source[targetBit]);
  }

  return value;
}


ScreenBuffer::ScreenBuffer() {
  clearBuffer();
}

ScreenBuffer::ScreenBuffer (bool source[8][8]) {
  loadBuffer(source);
}

ScreenBuffer::ScreenBuffer (byte source[8]) {
  loadBuffer(source);
}


void ScreenBuffer::loadBuffer (bool source[8][8]) {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    buffer[i] = boolArrayToByte(source[i]);
  }
}

void ScreenBuffer::loadBuffer (byte source[BUFFER_SIZE]) {
  if (source != NULL)
    memcpy(buffer, source, BUFFER_SIZE);
}

void ScreenBuffer::writeToBuffer(int row, int column, bool value) {
  if (row >= 0 && row <= 7 && column >= 0 && column <= 7) {
    byte targetRow = buffer[row];
    int targetColumnNumber = 7 - column;
    bitWrite(targetRow, targetColumnNumber, value);
    
    buffer[row] = targetRow;
  }
}

byte* ScreenBuffer::getBuffer() {
  return buffer;
}

void ScreenBuffer::clearBuffer() {
  for (int i = 0; i < 8; i++) {
    buffer[i] = 0;
  }
}

void ScreenBuffer::drawBuffer (LedControl lc, int screen = 0) {
  for (int i = 0; i < 8; i++) {
    lc.setRow(screen, i, buffer[i]);
  }
}

