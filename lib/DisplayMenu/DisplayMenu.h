#ifndef DisplayMenu_h
#define DisplayMenu_h

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <vector>
#include "Arduino.h"

using namespace std;

class DisplayMenu {
  private:
    vector<tuple<String, vector<String>>> menus;  // Items to print to the screen
    vector<tuple<String, vector<int>>> values;    // Values to the menu items (only used for servo angles)

    vector<String> currentMenu;
    vector<int> currentValues;


    int menuPage;
    int cursorPos;
    LiquidCrystal_I2C lcd;

    vector<String> getMenu(String pName);
    vector<int> getValues(String pName);

    

    

  public:
    DisplayMenu(LiquidCrystal_I2C pLCD);
    void addMenu(String pName, vector<String> pMenu);
    void addMenuPair(String pName, vector<String> pMenu);
    void printMenu(String pName);

    void setCursor(long pPos);
  
    int getLength(String pName);
    String select();
};

#endif