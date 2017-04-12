#ifndef SCREEN_BUFFER_INCLUDED
#define SCREEN_BUFFER_INCLUDED

#include <Arduino.h>
#include <LedControl.h>

#define BUFFER_SIZE 8 // in bytes

class ScreenBuffer {
  private:
    byte buffer[BUFFER_SIZE];
    
    byte boolArrayToByte(bool source[8]);

  public:
    ScreenBuffer();
    ScreenBuffer(bool source[8][8]);
    ScreenBuffer(byte source[BUFFER_SIZE]);
  
    void loadBuffer(bool source[8][8]);
    void loadBuffer(byte source[BUFFER_SIZE]);
    void writeToBuffer(int row, int column, bool value);
  
    byte* getBuffer();

    void clearBuffer();
    void drawBuffer(LedControl lc, int screen);
   
};



#endif
