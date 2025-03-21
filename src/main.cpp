#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include "AiEsp32RotaryEncoder.h"
#include <Display.h>
#include <vector>

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



const int LED1 = 35;


const int nServos = 6;


Display display(nServos);

Servo servos[nServos];
int servoPins[nServos] = {13, 25};
int servoAngles[nServos] = {0, 0};
int selectedServo = -1;



int rotary = 0;         //Value of rotary encoder
String option = "menu"; //Keep track of rotary encoder
std::vector<String> menu = {"BaseServo", "Shoulder", "Elbow", "Wrist", "Finger", "Fingertip"};

void setup() {
  pinMode(LED1, OUTPUT);
  Serial.begin(115200);


  for (int i = 0; i < nServos; i++){
    servos[i].attach(servoPins[i]);
  }

  display.init();
  display.printMenu(menu);
  rotaryEncoder.setBoundaries(0, menu.size()-1, false);
  

  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);

}

void loop(){ 
  if (rotaryEncoder.encoderChanged()){
    display.setCursor(rotaryEncoder.readEncoder());
  }


  if (rotaryEncoder.isEncoderButtonClicked()){
    Serial.println(display.select());
  }

}
