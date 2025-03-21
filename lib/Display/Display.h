#ifndef Display_h
#define Display_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <vector>
#include "Arduino.h"

class Display {
  private:
    int nServos;

    int menuPage;
    int cursorPos;
    std::vector<String> items;
    

  public:
    LiquidCrystal_I2C lcd;
    Display(int pnServos);
    void init();
    void printMenu(std::vector<String> pItems);

    void setCursor(long pPos);
    // void cursorUp();
    // void cursorDown();
    String select();
};

#endif