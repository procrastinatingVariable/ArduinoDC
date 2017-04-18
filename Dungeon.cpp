#include "Dungeon.h"

int Dungeon::dungeonInstances = 0;


Dungeon::Dungeon(Level& startMap) {

  // singleton class
  if (dungeonInstances == 1) return;

  int playerMaxRow = startMap.height * 8;
  int playerMaxColumn = startMap.width * 8;

  this->avatar = Player(playerMaxRow, playerMaxColumn);

  loadDungeon(startMap);

}


void Dungeon::loadDungeon (Level& dungeon) {
  dungeonWidth = dungeon.width;
  dungeonHeight = dungeon.height;

  int dungeonMapSize = computeDungeonMapSize(dungeon);
  loadRooms(dungeon.dungeomMap, dungeonMapSize);

  // initialize player position
  int playerStartingRow = 1;
  int playerStartingColumn = 1;
  placePlayer(dungeon.startRoom, playerStartingRow, playerStartingColumn);
}

