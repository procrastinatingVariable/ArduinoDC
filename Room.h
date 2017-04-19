#ifndef ROOM_INCLUDED
#define ROOM_INCLUDED

#include <Arduino.h>

class Room {
  private:
		static const int CHEST_WIDTH;
		static const int CHEST_HEIGHT;

    bool roomMap[8][8];

    void byteToBoolArray(bool dest[8], byte source);
    byte boolArrayToByte(bool source[8]);
		bool isInRoom(int row, int column);

  public:
    Room() = default;
    Room(const byte source[8]);
    Room(const bool source[8][8]);

    void loadRoom(const byte source[8]);
    void loadRoom(const bool source[8][8]);
    
		// get the room representation as a byte array
		// useful for loading the room into the screen buffer
    void getRoomByteArray(byte dest[8]);

		// adds a chest in the middle of the room if free
		bool addChest();
		// adds a chest at the given position if free
		bool addChest(int row, int column);
		
    // checks if specified position is free to move to
    bool checkIfFree(int row, int column);
		// checks if the given rectangle is free
		bool checkIfFree(int tRow, int tColumn,
										 int bRow, int bColumn);

    // for debugging
    void printRoomMap();
  
};

#endif
