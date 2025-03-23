#include "DisplayMenu.h"
#include "Arduino.h"
using namespace std;


DisplayMenu::DisplayMenu(LiquidCrystal_I2C pLCD) : lcd(0x27, 16, 4){
    lcd = pLCD;
}

void DisplayMenu::addMenu(String name, vector<String> pItems) {
    menus.push_back(make_tuple(name, pItems));
}

void DisplayMenu::addMenuPair(String name, vector<String> pItems) {
    vector<int> newValues;
    menus.push_back(make_tuple(name, pItems));
    values.push_back(make_tuple(name, newValues));
}

vector<String> DisplayMenu::getMenu(String pName){
    for (tuple<String, vector<String>>& menu : menus){
        if (get<0>(menu) == pName){
            currentMenu = get<1>(menu);
        }
    }
    return currentMenu;
}

vector<int> DisplayMenu::getValues(String pName){
    for (tuple<String, vector<int>>& menu : values){
        if (get<0>(menu) == pName){
            currentValues = get<1>(menu);
        }
    }
    return currentValues;
}

//Prints and selects menu as current menu
void DisplayMenu::printMenu(String pName){
    getMenu(pName);

    cursorPos = 0;
    menuPage = 0;
    setCursor(0);
    for (int i = 0; i < currentMenu.size() && i < 4; i++){
        lcd.setCursor(1, i);
        lcd.print(currentMenu[i]);
    }
}

void DisplayMenu::setCursor(long pPos){

    for (int i = 0; i < 4; i++){
        lcd.setCursor(0, i);
        lcd.print(" ");
    }

    cursorPos = pPos;

    //Switch menu
    if (floor(cursorPos/4) != menuPage){
        menuPage = floor(cursorPos/4);
        lcd.clear();
        for (int i = 0; i < 4 && menuPage * 4 + i < currentMenu.size(); i++){
            lcd.setCursor(1, i);
            lcd.print(currentMenu[menuPage*4+i]);
        }
    }

    if (cursorPos < 0){
        cursorPos = 0;
    }

    lcd.setCursor(0, cursorPos%4);
    lcd.print(">");
}

int DisplayMenu::getLength(String pName){
    getMenu(pName);
    return currentMenu.size();
}

String DisplayMenu::select(){
    return currentMenu[cursorPos];
}