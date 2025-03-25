#include <DisplayMenu.h>
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <AiEsp32RotaryEncoder.h>
using namespace std;

//Constructor
DisplayMenu::DisplayMenu(LiquidCrystal_I2C& pLCD, AiEsp32RotaryEncoder& pRE) : lcd(pLCD), rotaryEncoder(pRE) {
    editing = false;
    cursorShown = true;
}


//Private methods
vector<int> DisplayMenu::getValues(String pName){
    currentName = pName;
    for (tuple<String, vector<int>>& menu : values){
        if (get<0>(menu) == pName){
            currentValues = get<1>(menu);
        }
    }
    return currentValues;
}

vector<String> DisplayMenu::getMenu(String pName){
    currentName = pName;
    currentValues = {};

    for (tuple<String, vector<String>>& menu : menus){
        if (get<0>(menu) == pName){
            currentMenu = get<1>(menu);
        }
    }
    
    for (tuple<String, vector<int>>& value : values){
        if (get<0>(value) == pName){
            currentValues = get<1>(value);
        }
    }
    return currentMenu;
}

void DisplayMenu::saveValues(){
    for (int i = 0; i < values.size(); i++){
        if (get<0>(values[i]) == getSelected()){
            values[i] = make_tuple(get<0>(values[i]), currentValues);
        }
    }
}

void DisplayMenu::printNumber(int pNumber, int pPosY){
    lcd.setCursor(17, pPosY);
    lcd.print("000");
    if (pNumber < 10){
        lcd.setCursor(19, pPosY);
    } else if (pNumber < 100){
        lcd.setCursor(18, pPosY);
    } else {
        lcd.setCursor(17, pPosY);
    }

    lcd.print(pNumber);
}






//Public methods
void DisplayMenu::addMenu(String name, vector<String> pItems) {
    menus.push_back(make_tuple(name, pItems));
}

void DisplayMenu::addMenuPair(String name, vector<String> pItems) {
    vector<int> newValues;
    for (String& item : pItems){
        if (item != "Home"){
            newValues.push_back(0);
        }
    }
    menus.push_back(make_tuple(name, pItems));
    values.push_back(make_tuple(name, newValues));
}

void DisplayMenu::printMenu(String pName){
    getMenu(pName);
    lcd.clear();
    setCursor(0);

    rotaryEncoder.setBoundaries(0, getLength(getSelected())-1, false);
    cursorPos = 0;
    menuPage = 0;
    menuPage = floor(cursorPos/4);
    lcd.clear();
    for (int i = 0; i < 4 && menuPage * 4 + i < currentMenu.size(); i++){
        lcd.setCursor(1, i);
        lcd.print(currentMenu[menuPage*4+i]);
    }
    if (currentValues.size() != 0){

        for (int i = 0; i < 4 && menuPage * 4 + i < currentValues.size(); i++){
            printNumber(currentValues[menuPage*4+i], i);
        }
    }
    lcd.setCursor(0, 0);
    lcd.print(">");
}

void DisplayMenu::showCursor(){
    cursorShown= true;
    if (editing){
        lcd.setCursor(15, cursorPos);
    } else {
        lcd.setCursor(0, cursorPos);
    }

    lcd.print(">");
}

void DisplayMenu::hideCursor(){
    cursorShown = false;
    if (editing){
        lcd.setCursor(15, cursorPos);
    } else {
        lcd.setCursor(0, cursorPos);
    }

    lcd.print(" ");
}

pair<String, int> DisplayMenu::toggleEdit(){
    if (!editing){
        editing = true;
        lcd.setCursor(0, cursorPos%4);
        lcd.print(" ");
        lcd.setCursor(16, cursorPos%4);
        lcd.print(">");
        rotaryEncoder.setBoundaries(0, 180, false);
        return make_pair("", -1);
    } else {
        editing = false;
        lcd.setCursor(16, cursorPos%4);
        lcd.print(" ");
        lcd.setCursor(0, cursorPos%4);
        lcd.print(">");
        rotaryEncoder.setBoundaries(0, getLength(getSelected())-1, false);
        setCursor(cursorPos);
        rotaryEncoder.setEncoderValue(cursorPos);
        return make_pair(currentMenu[cursorPos], currentValues[cursorPos]);
    }
}



//Getters and setters
void DisplayMenu::setCursor(long pPos){
    if (!cursorShown){
        return;
    }

    if (editing){
        currentValues[cursorPos] = pPos;
        printNumber(currentValues[cursorPos], cursorPos);

        saveValues();
    } else {
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
            if (currentValues.size() != 0){
                for (int i = 0; i < 4 && menuPage * 4 + i < currentValues.size(); i++){
                    printNumber(currentValues[menuPage*4+i], i);
                }
            }
        }

        if (cursorPos < 0){
            cursorPos = 0;
        }

        lcd.setCursor(0, cursorPos%4);
        lcd.print(">");
    }
}

int DisplayMenu::getLength(String pName){
    getMenu(pName);
    return currentMenu.size();
}

String DisplayMenu::getSelected(){
    return currentName;
}

String DisplayMenu::select(){
    if (!editing && cursorShown){
        return currentMenu[cursorPos];
    } 
    return "";
}