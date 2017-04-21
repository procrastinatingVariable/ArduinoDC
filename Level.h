#ifndef LEVEL_INCLUDED
#define LEVEL_INCLUDED

#include <Arduino.h>
#include "maps.h"


struct Level {
  int width;
  int height;
  int startRoom;
  const byte* dungeonMap;
};

const Level dungeon1 = {3, 3, 0, map1};
const Level dungeon2 = {4, 4, 0, map2};



#endif


