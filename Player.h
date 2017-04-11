#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <Arduino.h>

class Player{
	private:
		int row;
		int column;

	public:
		Player();
		Player(int, int);

		void setRow(int);
		void setColumn(int);

		int getRow();
		int getColumn();

		bool moveUp();
		bool moveDown();
		bool moveLeft();
		bool moveRight();
};

#endif
