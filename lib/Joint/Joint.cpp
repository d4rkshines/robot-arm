#include <Wire.h>
#include "ESP32Servo.h"
#include "Joint.h"

Joint::Joint(int pPin) : pin(pPin), rotation(0) {}

void Joint::begin() {
    jointObj.attach(pin);
    Serial.print("Servo attached to pin: ");
    Serial.println(pin);
}

void Joint::setRotation(int pRotation) {
    rotation = pRotation;
    Serial.print("Setting rotation to: ");
    Serial.println(rotation);
    jointObj.write(rotation);
    delay(500);
}

int Joint::getRotation() {
    return rotation;
}
