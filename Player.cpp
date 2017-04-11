#include "Player.h"


Player::Player() {
	row = 0;
	column = 0;
}

Player::Player(int row, int column) {
	this->row = row;
	this->column = column;
}


void Player::setRow (int row) {
	if (row > 0 && row < 7) {
		this->row = row;
	}
}

void Player::setColumn (int column) {
	if (column > 0 && column < 7) {
		this->column = column;
	}
}

int Player::getRow() {
	return row;
}

int Player::getColumn() {
	return column;
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
	if (newRow <= 7) {
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
	if (newColumn <= 7) {
		column = newColumn;
		return true;
	}
	return false;
}
