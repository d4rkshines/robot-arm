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


const int nServos = 5;

std::vector<String> homeMenu = {"Servo Control", "Test Servos"};

std::vector<int> servoPins = {25, 13, -1, -1, -1};
std::vector<String> servoMenu = {"BaseServo", "Shoulder", "Elbow", "Wrist", "Finger", "Home"};
std::vector<Joint> servos;


DisplayMenu Menu(lcd, rotaryEncoder);

void setup() {
  Serial.begin(115200);

  Wire.begin();
  lcd.init();
  lcd.backlight();


  Menu.addMenu("home", homeMenu);
  Menu.addMenuPair("servos", servoMenu);
  Menu.printMenu("home");


  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  rotaryEncoder.setBoundaries(0, Menu.getLength(Menu.getSelected())-1, false);

  for (int i = 0; i < nServos; i++){
    servos.push_back(Joint(servoPins[i]));
  }

  servos[0].setRotation(90);
  Serial.println(servoPins[0]);
  Serial.println(servos[0].getRotation());

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
    } else {
      pair<String, int> result = Menu.toggleEdit();
      if (result.first != "" && result.second != -1){
        int servoIndex;
        for (int i = 0; i < servoMenu.size(); i++){
          if (servoMenu[i] == result.first){
            servoIndex = i;
          }
        }
        Serial.println(result.first + " to rotation " + result.second);
        servos[servoIndex].setRotation(result.second);
      }
    }
  }

}
