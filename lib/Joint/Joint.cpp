#include "Joint.h"
#include "ESP32Servo.h"


Joint::Joint(int pPin){
    jointObj = Servo();
    jointObj.attach(pin);
}

void Joint::setRotation(int pRotation){
    rotation = pRotation;
    jointObj.write(rotation);
};

int Joint::getRotation(){
    return rotation;
};