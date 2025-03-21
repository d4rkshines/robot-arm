#include "Display.h"
#include "Arduino.h"


Display::Display(int pnServos) : lcd(0x27, 16, 4) {
    nServos = pnServos;
    LiquidCrystal_I2C lcd(0x27, 16, 4);
}

void Display::init(){
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(">");
}

void Display::printMenu(std::vector<String> pItems){
    items = pItems;
    cursorPos = 0;
    setCursor(0);
    for (int i = 0; i < items.size() && i < 4; i++){
        lcd.setCursor(1, i);
        lcd.print(items[i]);
    }
}

void Display::setCursor(long pPos){
    for (int i = 0; i < 4; i++){
        lcd.setCursor(0, i);
        lcd.print(" ");
    }

    cursorPos = pPos;
    menuPage = floor(cursorPos/4);
    if (cursorPos > 3){
        cursorPos = cursorPos - menuPage;
    } else if (cursorPos < 0){
        cursorPos = 0;
    }
    lcd.setCursor(0, cursorPos);
    lcd.print(">");
}

// void Display::cursorUp(){
//     if (cursorPos > 0){
//         lcd.setCursor(0, cursorPos);
//         lcd.print(" ");
//         cursorPos--;
//         lcd.setCursor(0, cursorPos);
//         lcd.print(">");
//         cursorSelect--;
//     } else if (cursorPos == 0 && cursorSelect > 0){
//         cursorSelect--;
//         for (int i = 0; i < 4 && i+cursorSelect < items.size(); i++){
//             lcd.setCursor(1, i);
//             for (int i = 0; i < 15; i++){
//                 lcd.print(" ");
//             }
//             lcd.setCursor(1, i);
//             lcd.print(items[i+cursorSelect]);
//         }
//     }
// }

// void Display::cursorDown(){
//     if (cursorPos < 3){
//         lcd.setCursor(0, cursorPos);
//         lcd.print(" ");
//         cursorPos++;
//         lcd.setCursor(0, cursorPos);
//         lcd.print(">");
//         cursorSelect++;
//     } else if (cursorPos == 3){
//         cursorSelect++;
//         for (int i = 0; i < 4 && i+cursorSelect-4 < items.size(); i++){
//             lcd.setCursor(1, i);
//             for (int i = 0; i < 15; i++){
//                 lcd.print(" ");
//             }
//             lcd.setCursor(1, i);
//             lcd.print(items[i+cursorSelect-3]);
//         }
//     }
// }


String Display::select(){
    return items[cursorPos];
}