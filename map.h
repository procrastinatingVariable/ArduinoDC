#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <Arduino.h>

#define MAX_MAP_SIZE 200 // in bytes, corresponds to a 25 rooms

struct Level {
  int width;
  int height;
  int startRoom;
  byte dungeonMap[MAX_MAP_SIZE];
};


const Level dungeon1 = {2, 2, 0,
                            { B11111111,
                              B10000001,
                              B10000001,
                              B10000000,
                              B10000000,
                              B10000001,
                              B10000001,
                              B11001111,
                              // second room
                              B11111111,
                              B10000001,
                              B10000001,
                              B00000001,
                              B00000001,
                              B10000001,
                              B10000001,
                              B11001111,
                              // third room
                              B11001111,
                              B10000001,
                              B10000001,
                              B10000000,
                              B10000000,
                              B10000001,
                              B10000001,
                              B11111111,
                              // forth room
                              B11001111,
                              B10000001,
                              B10000001,
                              B00000001,
                              B00000001,
                              B10000001,
                              B10000001,
                              B11111111 } };

               
#endif
