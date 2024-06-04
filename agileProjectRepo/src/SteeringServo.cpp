/*
 * SteeringServo.cpp
 */

#include <Arduino.h>
#include "Motors/SteeringServo.h"

SteeringServo::SteeringServo(int engineServoPIN)
{
    servoPIN = engineServoPIN;
}

SteeringServo::~SteeringServo()
{
}

void SteeringServo::initiateServo()
{
    servoObject.attach(servoPIN);
    // 60 is the middle of a 120 degree servo
    servoObject.write(60);
    servoObject.setPeriodHertz(50);
}

void SteeringServo::setDirection(int inDirection)
{
    // The servo used is a 120 degree servo and requires a
    //  input value between 0 and 120, therefore the input
    //  is remapped.
    int newDirection = map(inDirection, 0, 4096, 0, 120);
    if (newDirection == direction)
    {
        return;
    }
    direction = newDirection;
    servoObject.write(newDirection);
}