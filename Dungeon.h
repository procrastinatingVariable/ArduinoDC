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
  
    Room** dungeonRooms;
    Player* avatar;

    int computeDungeonMapSize(); // in bytes
    void loadRooms(const byte* dungeonMap);

  public:
    Dungeon();
    Dungeon(const Level& startMap);

    // loads the rooms and places the player in the starting position
    void loadDungeon(const Level& dungeon);

    // gets player instance
    Player* getPlayer();

    // returns the number of the room the player's currently in
    int getPlayerRoomNumber();

    // returns the number of rooms
    int getRoomNumber();

    // returns a reference to the room with the given number
    Room& getRoom(int number);
    // same as above but give grid index values
    Room& getRoom(int row, int column);
    
    // places the player in the given room at the given coordinates
    bool placePlayer(int roomNumber, int playerRow, int playerCol);
    // same as above but give grid index values for the room
    bool placePlayer(int roomRowIndex, int roomColIndex, int playerRow, int playerCol);


    // for debugging
    void freeRoomMemory();

    // destructor
    ~Dungeon();
    
  
};


#endif
