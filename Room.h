#ifndef ROOM_INCLUDED
#define ROOM_INCLUDED

#include <Arduino.h>

class Room {
  private:
    bool roomMap[8][8];

    void byteToBoolArray(bool dest[8], byte source);

  public:
    Room(byte source[8]);
    Room(bool source[8][8]);

    void loadRoom(byte source[8]);
    void loadRoom(bool source[8][8]);

    // checks if specified position is free to move to
    bool checkIfFree(int row, int column);
  
};

#endif
