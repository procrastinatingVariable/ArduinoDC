#include "Player.h"


Player::Player(int playerMaxRow, int playerMaxColumn) {
  this->playerMaxRow = playerMaxRow;
  this->playerMaxColumn = playerMaxColumn;
  this->row = 1;
  this->column = 1;
}

Player::Player(int row, int playerMaxRow, 
               int column, int playerMaxColumn) {
  this->row = row;
  this->playerMaxRow = playerMaxRow;
  this->column = column;
  this->playerMaxColumn = playerMaxColumn;
}


void Player::setRowAbsolute (int row) {
  if (row >= 0 && row <= playerMaxRow) {
    this->row = row;
  }
}

void Player::setColumnAbsolute (int column) {
  if (column >= 0 && column <= playerMaxColumn) {
    this->column = column;
  }
}

void Player::setRowRelative (int row) {
  if (row >= 0 && row <= 7) {
    int newRowOffset = row - getRowRelative();
    this->row += newRowOffset;
  }
}

void Player::setColumnRelative (int column) {
  if (column >= 0 && column <= 7) {
    int newColumnOffset = column - getColumnRelative();
    this->column += newColumnOffset;
  }
}


int Player::getRowAbsolute() {
  return row;
}

int Player::getColumnAbsolute() {
  return column;
}

int Player::getRowRelative() {
  return row % 8;
}

int Player::getColumnRelative() {
  return column % 8;
}





bool Player::moveUp() {
	int newRow = row - 1;
  if (newRow >= 0) {
	  row = newRow;
	  return true;
  }
  return false;
}

bool Player::moveDown() {
	int newRow = row + 1;
  if (newRow <= playerMaxRow) {
	  row = newRow;
	  return true;
  }
  return false;
}

bool Player::moveLeft() {
	int newColumn = column - 1;
  if (newColumn >= 0) {
  	column = newColumn;
  	return true;
  }
  return false;
}

bool Player::moveRight() {
	int newColumn = column + 1;
  if (newColumn <= playerMaxColumn) {
  	column = newColumn;
  	return true;
  }
  return false;
}
