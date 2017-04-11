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
  } else if (c.getUpState() == Controler::BUTTON_PRESSED) {
    p.moveUp();
  } else if (c.getDownState() == Controler::BUTTON_PRESSED) {
    p.moveDown();
  }
  getRoom(0);
  displayScreen();
  displayPlayer();

  delay(150);
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

void displayPlayer() {
  lc.setLed(0, p.getRow(), p.getColumn(), HIGH);
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

