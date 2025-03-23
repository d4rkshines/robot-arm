#include <Arduino.h>
#include <vector>
#include <Wire.h>
#include <ESP32Servo.h>
#include <AiEsp32RotaryEncoder.h>
#include <LiquidCrystal_I2C.h>

#include <DisplayMenu.h>
#include <Joint.h>

#define ROTARY_ENCODER_DT_PIN 32
#define ROTARY_ENCODER_CLK_PIN 33
#define ROTARY_ENCODER_SW_PIN 14
#define ROTARY_ENCODER_VCC_PIN -1
#define ROTARY_ENCODER_STEPS 4

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_DT_PIN, ROTARY_ENCODER_CLK_PIN, ROTARY_ENCODER_SW_PIN, ROTARY_ENCODER_VCC_PIN, ROTARY_ENCODER_STEPS);

void IRAM_ATTR readEncoderISR()
{
    rotaryEncoder.readEncoder_ISR();
}


LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 4);



int rotary = 0;         //Value of rotary encoder
String option = "menu"; //Keep track of rotary encoder

std::vector<String> HomeMenu = {"Servo Control"};
std::vector<String> ServoMenu = {"BaseServo", "Shoulder", "Elbow", "Wrist", "Finger", "Fingertip", "Home"};

DisplayMenu Menu(lcd, rotaryEncoder);

void setup() {
  Serial.begin(115200);

  Wire.begin();
  lcd.init();
  lcd.backlight();


  Menu.addMenu("home", HomeMenu);
  Menu.addMenuPair("servos", ServoMenu);
  Menu.printMenu("home");


  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  rotaryEncoder.setBoundaries(0, Menu.getLength(Menu.getSelected())-1, false);

}

void loop(){ 
  if (rotaryEncoder.encoderChanged()){
    Menu.setCursor(rotaryEncoder.readEncoder());
  }


  if (rotaryEncoder.isEncoderButtonClicked()){
    String selected = Menu.select();
    if (selected == "Home"){
      Menu.printMenu("home");
    } else if (selected == "Servo Control"){
      Menu.printMenu("servos");
    }
  }

}
