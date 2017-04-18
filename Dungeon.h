#ifndef DUNGEON_INCLUDED
#define DUNGEON_INCLUDED

#include "map.h" // this will be renamed
#include "Room.h"
#include "Player.h"

class Dungeon {
  private:
    static int dungeonInstances;

    int dungeonWidth; // in number of rooms
    int dungeonHeight; // in number of rooms
  
    Room* dungeonRooms;
    Player avatar;

    int computeDungeonMapSize(Level& dungeon); // in bytes
    void loadRooms(byte* dungeonMap, int mapSize);

  public:
    Dungeon(Level& startMap);

    // loads the rooms and places the player in the starting position
    void loadDungeon(Level& dungeon);

    // gets player instance
    Player& getPlayer();

    // returns the number of the room the player's currently in
    int getPlayerRoomNumber();

    // returns a reference to the room with the given number
    Room& getRoom(int number);
    
    // places the player in the given room at the given coordinates
    void placePlayer(int roomNumber, int row, int column);
    

    // destructor
    ~Dungeon();
    
  
};


#endif
