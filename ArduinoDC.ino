#include "Controler.h"
#include "ScreenBuffer.h"
#include "Dungeon.h"

#include <MemoryFree.h>
#include <LiquidCrystal.h>
#include <LedControl.h>


#define CLOCK_PIN 9
#define LOAD_PIN 8
#define DATA_IN_PIN 10

#define LEFT_BUTTON_PIN 4
#define RIGHT_BUTTON_PIN 2
#define UP_BUTTON_PIN 3
#define DOWN_BUTTON_PIN 5
#define ACTION_BUTTON_PIN 6

#define LCD_RS A0
#define LCD_ENABLE A1
#define LCD_D4 A2
#define LCD_D5 A3
#define LCD_D6 A4
#define LCD_D7 A5

#define NUM_OF_KEYS 3
#define MAX_LEVEL 2

#define ALLOTTED_TIME 60 // in seconds



LedControl lc(DATA_IN_PIN, CLOCK_PIN, LOAD_PIN, 1);
LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

Dungeon* d;
Player* p;
Controler c(LEFT_BUTTON_PIN, RIGHT_BUTTON_PIN, UP_BUTTON_PIN, DOWN_BUTTON_PIN, ACTION_BUTTON_PIN);
ScreenBuffer b;

int currentLevel;
bool gatewayAdded;
unsigned long int timerStart;


void setup() {
  Serial.begin(9600);

  initScreen();
  initMonitor();
  initDungeon();

}

void loop() {
  c.readButtons();

  if (secondsSinceTimerStart() > ALLOTTED_TIME) {
    endGame();
  }


  movePlayer();

  drawRoom();
  displayPlayer();
  doAction();

  if (p->getKeys() == NUM_OF_KEYS && gatewayAdded == 0) {
    placeGate();
    gatewayAdded = 1;
  }

  // change to next dungeon if the player found the gateway
  int currentRoomNum = d->getPlayerRoomNumber();
  if (gatewayAdded) {
    Room& currentRoom = d->getRoom(currentRoomNum);
    int playerRow = p->getRowRelative();
    int playerCol = p->getColumnRelative();
    if (currentRoom.isInGate(playerRow, playerCol)) {
      currentLevel++;

      if (currentLevel > MAX_LEVEL) {
        winGame();
      }
      
      loadLevel(currentLevel);
    }
  }


  b.drawBuffer(lc, 0);
  updateMonitor();

  if (levelChanged()) {
    displayNewLevelMessage();
  }
  
  delay(150);
}


void endGame() {
  lcd.clear();
  lcd.print("GAME OVER");

  // block the game
  while(1){};
}

bool levelChanged() {
  static int lastLevel = -1;
  
  bool levelChanged = 0;
  if (lastLevel != currentLevel) {
    levelChanged = 1;
    lastLevel = currentLevel;
  }

  return levelChanged;
}

void winGame() {
  lcd.clear();
  lcd.print("YOU'RE FREE");

  byte smiley[] = { B00000000,
                    B00100100,
                    B00100100,
                    B00000000,
                    B00000000,
                    B10000001,
                    B01000010,
                    B00111100 };
                    
  b.loadBuffer(smiley);
  b.drawBuffer(lc, 0);

  while(1) {};
}




/******************************************
 ***************TIME RELATED**************
 ******************************************/

int secondsSinceTimerStart() {
  return (millis() - timerStart) / 1000;
}



/******************************************
 ****************LCD SCREEN MONITOR********
 ******************************************/
void initMonitor() {
  lcd.begin(16, 2);
}

void updateMonitor() {
  lcd.clear();

  lcd.print("Keys: ");
  lcd.print(p->getKeys());
  lcd.print("/");
  lcd.print(NUM_OF_KEYS);

  // place the cursor to a new line
  lcd.setCursor(0, 1);
  lcd.print("Time left:");
  lcd.print(ALLOTTED_TIME - secondsSinceTimerStart());
}

void displayNewLevelMessage() {
  lcd.clear();
  
  lcd.print("DUNGEON ");
  lcd.print(currentLevel);
  
  int secondsLeft = 3;
  while (secondsLeft >= 0) {
    lcd.setCursor(0, 1);
    lcd.print(secondsLeft);
  
    delay(1000);
    secondsLeft--;
  }
}


/******************************************
 ***************LEVEL RELATED**************
 ******************************************/
void initDungeon() {
  currentLevel = 1;
  d = new Dungeon();
  loadLevel(currentLevel);

  p = d->getPlayer();

}

void loadLevel (int levelNum) {
  Serial.println("************************");
  Serial.print("Loaded level : ");
  Serial.println(currentLevel);
  Serial.println("************************");

  // reset the number of keys the player has
  p->setKeys(0);
  gatewayAdded = 0;

  timerStart = millis();

  switch (levelNum) {
    case 1:
      d->loadDungeon(dungeon1);
      break;

    case 2:
      d->loadDungeon(dungeon2);
      break;

    default:
      d->loadDungeon(dungeon1);
  }

  initKeys();
}

void initKeys() {
  randomSeed(analogRead(0));
  int playerStartingRoom = d->getPlayerRoomNumber();
  int numOfRooms = d->getRoomNumber();

  int keyLocations[3];
  for (int i = 0; i < NUM_OF_KEYS; i++) {
    int rRoom;
    // generate numbers untill you found one of a room who's empty (player or chest)
    while ((rRoom = random(0, numOfRooms)) == playerStartingRoom ||
           d->getRoom(rRoom).hasChest()) {}

    d->getRoom(rRoom).addChest();
    Serial.print("Added a chest in room ");
    Serial.println(rRoom);
  }

}

void placeGate() {
  randomSeed(analogRead(0));
  int playerCurrentRoom = d->getPlayerRoomNumber();
  int numOfRooms = d->getRoomNumber();

  int rRoom;
  while ((rRoom = random(0, numOfRooms)) == playerCurrentRoom) {}

  d->getRoom(rRoom).addGateway();
  Serial.print("Gateway to next level added to room ");
  Serial.println(rRoom);
}





/******************************************
 **************PLAYER RELATED**************
 ******************************************/
void movePlayer() {
  int currentRoomNumber = d->getPlayerRoomNumber();
  Room& currentRoom = d->getRoom(currentRoomNumber);
  if (c.getUpState() == Controler::BUTTON_PRESSED) {
    p->move(Player::MOVE_UP, currentRoom);
  } else if (c.getDownState() == Controler::BUTTON_PRESSED) {
    p->move(Player::MOVE_DOWN, currentRoom);
  } else if (c.getLeftState() == Controler::BUTTON_PRESSED) {
    p->move(Player::MOVE_LEFT, currentRoom);
  } else if (c.getRightState() == Controler::BUTTON_PRESSED) {
    p->move(Player::MOVE_RIGHT, currentRoom);
  }
}

void doAction() {
  String debugS = "Player has collected the key in room #";

  int currentRoomNumber = d->getPlayerRoomNumber();
  Room& currentRoom = d->getRoom(currentRoomNumber);

  int pRow = p->getRowRelative();
  int pCol = p->getColumnRelative();
  if (c.getActionState() == Controler::BUTTON_PRESSED) {
    if (currentRoom.hasChest()) {
      if (currentRoom.isNearChest(pRow, pCol)) {
        p->addKey();
        currentRoom.removeChest();

        debugS += currentRoomNumber;
        Serial.println(debugS);
      }
    }

    if (currentRoom.isInGate (pRow, pCol)) {
      Serial.println("Player is in the gate!");
    }
  }
}






/******************************************
 ************GRAPHICS**********************
 ******************************************/
void initScreen() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 10);
  lc.clearDisplay(0);

}

void drawRoom() {
  byte* roomByteArray;
  int roomNumber = d->getPlayerRoomNumber();
  roomByteArray = d->getRoom(roomNumber).getRoomByteArray();
  b.loadBuffer(roomByteArray);
}

void displayPlayer() {
  int playerRow = p->getRowRelative();
  int playerColumn = p->getColumnRelative();
  b.writeToBuffer(playerRow, playerColumn, 1);
}

