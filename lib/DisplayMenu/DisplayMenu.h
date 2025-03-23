#ifndef DisplayMenu_h
#define DisplayMenu_h

#include "Arduino.h"
#include <Wire.h>
#include <vector>

#include <LiquidCrystal_I2C.h>
#include <AiEsp32RotaryEncoder.h>

using namespace std;

class DisplayMenu {
  private:
    LiquidCrystal_I2C& lcd;
    AiEsp32RotaryEncoder& rotaryEncoder;



    vector<tuple<String, vector<String>>> menus;  // Items to print to the screen
    vector<tuple<String, vector<int>>> values;    // Values to the menu items (only used for servo angles)

    vector<String>  currentMenu;
    vector<int>     currentValues;
    String          currentSelected;   // Name of selected menu/values

    int menuPage;
    int cursorPos;

    vector<String> getMenu(String pName);
    vector<int> getValues(String pName);



    

  public:
    DisplayMenu(LiquidCrystal_I2C& pLCD, AiEsp32RotaryEncoder& pRE);
    void addMenu(String pName, vector<String> pMenu);
    void addMenuPair(String pName, vector<String> pMenu);
    void printMenu(String pName);

    void setCursor(long pPos);
  
    int getLength(String pName);
    String getSelected();
    String select();
};

#endif