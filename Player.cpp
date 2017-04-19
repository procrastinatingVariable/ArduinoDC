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

  this->row = 0;
  if (row >= 0) {
    this->row = row;
  }
}

void Player::setColumnAbsolute (int column) {
  this->column = 0;
  if (column >= 0) {
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




// GOTTA FIX THIS SHIT!
// COLLISION SYSTEM DOESN'T LET YOU MOVE OUT THE ROOM
bool Player::move (int direction, Room& roomContext) {
	
	int row = getRowRelative();
	int column = getColumnRelative();
	int oldRow = row;
	int oldColumn = column;

  switch (direction) {
    case MOVE_UP : 
      row--;
      break;

    case MOVE_DOWN : 
      row++;
      break;

    case MOVE_LEFT : 
      column--;
      break;

    case MOVE_RIGHT : 
      column++;
      break;

    default :
      return 0;
      
  }

	if (!roomContext.checkIfFree(row, column)) {
		row = oldRow;
		column = oldColumn;
		return 0;
	}

	int rowOffset = row - oldRow;
	int columnOffset = column - oldColumn;
	int newRowAbsolute = getRowAbsolute() + rowOffset;
	int newColumnAbsolute = getColumnAbsolute() + columnOffset;
	setRowAbsolute(newRowAbsolute);
	setColumnAbsolute(newColumnAbsolute);

	
  return 1;
}


