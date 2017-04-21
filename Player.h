#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <Arduino.h>

#include "Room.h"

class Player{
	private:
    // absolute (dungeon) coordinates of the player
		int row;
    int column;

    int collectedKeys;

	public:
    static const int MOVE_UP = 8;
    static const int MOVE_DOWN = 2;
    static const int MOVE_LEFT = 4;
    static const int MOVE_RIGHT = 6;
 
    Player();
    Player(int row, int column);

           
    // set position in dungeon
    void setRowAbsolute(int row);
    void setColumnAbsolute(int column);

    // set position in current room
    void setRowRelative(int row);
		void setColumnRelative(int column);


    int getKeys();
    void setKeys(int num);
    void addKey();
    void removeKey();
   

    // get position in dungeon
    int getRowAbsolute();
    int getColumnAbsolute();
    
    // get position in current room
		int getRowRelative();
		int getColumnRelative();

		bool move (int direction, Room& roomContext);

};

#endif
