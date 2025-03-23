#include <Arduino.h>
#include <unity.h>
#include <DisplayMenu.h>
#include <LiquidCrystal_I2C.h>
#include <vector>
#include <string>
using namespace std;


LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 4);

DisplayMenu Menu(lcd);

vector<String> menu1 = {"item1", "item2", "item3"};
vector<String> menu2 = {"2 item1", "2 item2", "2 item3"};



void test_menu_length(void){
    TEST_ASSERT_EQUAL(3, Menu.getLength("menu1"));
}

void test_menu_select(void){
    Menu.setCursor(1);
    TEST_ASSERT_EQUAL_STRING("item2", Menu.select().c_str());
}

void test_switch_menu_select(void){
    Menu.printMenu("menu2");
    TEST_ASSERT_EQUAL_STRING("2 item1", Menu.select().c_str());
}


void setup()
{
  // NOTE!!! Wait for >2 secs
  // if board doesn't support software reset via Serial.DTR/RTS
  delay(2000);

  Menu.addMenu("menu1", menu1);
  Menu.addMenu("menu2", menu2);
  

  UNITY_BEGIN(); // IMPORTANT LINE!
  RUN_TEST(test_menu_length);
  RUN_TEST(test_menu_select);
  RUN_TEST(test_switch_menu_select);



  UNITY_END();
}

void loop(){
    
}