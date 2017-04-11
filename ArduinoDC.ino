#include "map.h"
#include <LedControl.h>
#include "Controler.h"
#include "Player.h"

#define CLOCK_PIN 6
#define LOAD_PIN 8
#define DATA_IN_PIN 7

#define LEFT_BUTTON_PIN 11
#define RIGHT_BUTTON_PIN 10
#define UP_BUTTON_PIN 9
#define DOWN_BUTTON_PIN 12

/*
class Player {
  private:
    int row;
    int column;

  public:
    Player() {
      row = 0;
      column = 0;
    }
  
    Player(int row, int column) {
      this->row = row;
      this->column = column;
    }

    void setRow (int row) {
      if (row > 0 && row < 7)
        this->row = row;
    }

    void setColumn (int column) {
      if (column > 0 && column < 7)
        this->column = column;
    }

    int getRow() {
      return row;
    }

    int getColumn() {
      return column;
    }

    bool moveUp() {
      int newRow = row - 1;
      if (newRow >= 0) {
        row = newRow;
        return true;
      }
      return false;
    }

    bool moveDown() {
      int newRow = row + 1;
      if (newRow <= 7) {
        row = newRow;
        return true;
      }
      return false;
    }

    bool moveLeft() {
      int newColumn = column - 1;
      if (newColumn >= 0) {
        column = newColumn;
        return true;
      }
      return false;
    }

    bool moveRight() {
      int newColumn = column + 1;
      if (newColumn <= 7) {
        column = newColumn;
        return true;
      }
      return false;
    }
    
};

class Controler {
  private:
    bool leftButton;
    bool rightButton;
    bool upButton;
    bool downButton;

    int leftButtonPin;
    int rightButtonPin;
    int upButtonPin;
    int downButtonPin;

    unsigned static const long int readDisableTime = 25; // millis
    unsigned static long int timerStart;

    bool readButtonState (int buttonPin) {
      bool readValue = !digitalRead(buttonPin);
      return readValue;
    }

    bool validate (bool initialButtonValue, int buttonPin) {
      int newValue = readButtonState(buttonPin);
      return newValue == initialButtonValue;
    }

  public:
    static const bool BUTTON_PRESSED  = HIGH;
    static const bool BUTTON_RELEASED = LOW;

    Controler() {      
      leftButton = BUTTON_RELEASED;
      rightButton = BUTTON_RELEASED;
      upButton = BUTTON_RELEASED;
      downButton = BUTTON_RELEASED;
    }

    Controler(int leftButtonPin,
              int rightButtonPin,
              int upButtonPin,
              int downButtonPin) {
      Controler();

      this->leftButtonPin = leftButtonPin;
      this->rightButtonPin = rightButtonPin;
      this->upButtonPin = upButtonPin;
      this->downButtonPin = downButtonPin;

      pinMode(leftButtonPin, INPUT_PULLUP);
      pinMode(rightButtonPin, INPUT_PULLUP);
      pinMode(upButtonPin, INPUT_PULLUP);
      pinMode(downButtonPin, INPUT_PULLUP);
    }

    bool getLeftState() {
      return leftButton;
    }

    bool getRightState() {
      return rightButton;
    }

    bool getUpState() {
      return upButton;
    }

    bool getDownState() {
      return downButton;
    }

    void readButtons() {
      static unsigned long int timerStart = 0;
      
      if (millis() - timerStart > readDisableTime) {
      
        bool leftReadValue = readButtonState(leftButtonPin);
        bool rightReadValue = readButtonState(rightButtonPin);
        bool upReadValue = readButtonState(upButtonPin);
        bool downReadValue = readButtonState(downButtonPin);
        
        //delay(15);
  
        if (validate(leftReadValue, leftButtonPin)) {
          leftButton = leftReadValue;
        }
        if (validate(rightReadValue, rightButtonPin)) {
          rightButton = rightReadValue;
        }
        if (validate(upReadValue, upButtonPin)) {
          upButton = upReadValue;
        }
        if (validate(downReadValue, downButtonPin)) {
          downButton = downReadValue;
        }

        
        timerStart = millis();
      }

    }
    
};
*/

bool currentScreen[8][8];
Player p;
Controler c;

LedControl lc = LedControl(DATA_IN_PIN, CLOCK_PIN, LOAD_PIN, 1);

void setup() {
  Serial.begin(9600);
  
  lc.shutdown(0, false);
  lc.setIntensity(0, 10);
  lc.clearDisplay(0);

  p = Player(6, 1);
  c = Controler(LEFT_BUTTON_PIN, RIGHT_BUTTON_PIN, UP_BUTTON_PIN, DOWN_BUTTON_PIN);
}

int currentScreenNumber = 0;
void loop() {
  lc.clearDisplay(0);
  c.readButtons();

  Serial.print(p.getRow());
  Serial.print(" ");
  Serial.println(p.getColumn());

  if (c.getLeftState() == Controler::BUTTON_PRESSED) {
    p.moveLeft();
  } else if (c.getRightState() == Controler::BUTTON_PRESSED) {
    p.moveRight();
  }

  delay(250);
}

void getRoom(int roomNumber) {
  byte rawRoom[8];
  memcpy(rawRoom, map2 + roomNumber * 8, 8);

  for (int i = 0; i < 8; i++) {
    byte currentRow = rawRoom[i];
    for (int j = 0; j < 8; j++) {
      currentScreen[i][j] = bitRead(currentRow, 7 - j);
    }
  }
}

byte arrayToByte(bool source[8]) {
  byte endValue;
  for (int i = 0; i < 8; i++) {
    bitWrite(endValue, 7 - i, source[i]);
  }
  return endValue;
}

void displayScreen() {
  byte rowValue;
  for (int i = 0; i < 8; i++) {
    rowValue = arrayToByte(currentScreen[i]);
    lc.setRow(0, i, rowValue);
  }
}

void printScreenDebug() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Serial.print(currentScreen[i][j]);
      Serial.print(" ");
    }
    Serial.println("");
  }
  Serial.println("------------------------------");
}

