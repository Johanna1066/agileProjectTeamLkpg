/*
 * SteeringServo.cpp
 */

#include <Arduino.h>
#include "Motors/steeringServo.h"

/**
 * @brief Constructs a SteeringServo object.
 *
 * @param engineServoPIN The pin number where the servo is connected.
 */
SteeringServo::SteeringServo(int engineServoPIN)
{
    servoPIN = engineServoPIN;
}

/**
 * @brief Initializes the servo.
 *
 * Performs all necessary electronic setup for the hardware to work properly.
 */
void SteeringServo::initiateServo()
{
    servoObject.attach(servoPIN);
    // 60 is the middle of a 120 degree servo
    servoObject.write(60);
    servoObject.setPeriodHertz(50);
}

/**
 * @brief Sets the direction of the servo.
 *
 * @param newDirection The new direction to set, rescaled using the Arduino
 * map function to the desired range for the servo.
 */
void SteeringServo::setDirection(int inDirection)
{
    /**
     * The servo used is a 120 degree servo and requires a
     *  input value between 0 and 120, therefore the input
     *  is remapped.
     */
    int newDirection = map(inDirection, 0, 4096, 0, 120);
    if (newDirection == direction)
    {
        return;
    }
    direction = newDirection;
    servoObject.write(newDirection);
}