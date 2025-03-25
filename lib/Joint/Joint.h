#ifndef Joint_h
#define Joint_h

#include <Wire.h>
#include <vector>
#include "Arduino.h"
#include <ESP32Servo.h>

class Joint {
  private:
    Servo jointObj;
    int pin;
    int rotation;
    int speed = 0.005; // sec/degree
     

  public:
    Joint(int pin);
    void begin();
    void setRotation(int rotation);
    int getRotation();
};

#endif