#include <Arduino.h>
#include <iostream>

#include "sensorClass.h"

int delayTime = 1000;

joyStick testJoystick(A3, A4, 5);


void setup()
{
    Serial.begin(9600);
    testJoystick.initiateJoystick();

}

void loop()
{
    testJoystick.vertialRead();
    delay(delayTime);
    testJoystick.horizontalRead();
    delay(delayTime);
}
