#ifndef ROOM_INCLUDED
#define ROOM_INCLUDED

#include <Arduino.h>

class Room {
  private:
    bool roomMap[8][8];

    void byteToBoolArray(bool dest[8], byte source);
    byte boolArrayToByte(bool source[8]);

  public:
    Room() = default;
    Room(const byte source[8]);
    Room(const bool source[8][8]);

    void loadRoom(const byte source[8]);
    void loadRoom(const bool source[8][8]);
    
    void getRoomByteArray(byte dest[8]);

    // checks if specified position is free to move to
    bool checkIfFree(int row, int column);

    // for debugging
    void printRoomMap();
  
};

#endif
