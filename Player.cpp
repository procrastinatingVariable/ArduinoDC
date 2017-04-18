#include "Player.h"


Player::Player () {
  setRowAbsolute(0);
  setColumnAbsolute(0);
}

Player::Player (int row, int column) {
  setRowAbsolute(row);
  setColumnAbsolute(column);
}


void Player::setRowAbsolute (int row) {
  this->row = row ? row >= 0 : 0;
}

void Player::setColumnAbsolute (int column) {
  this->column = column ? column >= 0 : 0;
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
  row = newRow;
  return true;
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
	column = newColumn;
	return true;
}
