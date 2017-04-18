#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <Arduino.h>

class Player{
	private:
    // absolute (dungeon) coordinates of the player
		int row;
		int column;

	public:
    Player();
    Player(int row, int column);

           
    // set position in dungeon
    void setRowAbsolute(int row);
    void setColumnAbsolute(int column);

    // set position in current room
    void setRowRelative(int row);
		void setColumnRelative(int column);


   

    // get position in dungeon
    int getRowAbsolute();
    int getColumnAbsolute();
    
    // get position in current room
		int getRowRelative();
		int getColumnRelative();

		bool moveUp();
		bool moveDown();
		bool moveLeft();
		bool moveRight();
};

#endif
