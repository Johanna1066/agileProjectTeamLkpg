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
    servoObject.write(60);
    servoObject.setPeriodHertz(50);
}

void SteeringServo::setDirection(int inDirection)
{
    int newDirection = map(inDirection, 0, 4096, 0, 119);
    if (newDirection == direction)
    {
        return;
    }
    direction = newDirection;
    servoObject.write(newDirection);
}