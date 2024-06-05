/*
 * Engine.cpp
 */

#include <Arduino.h>
#include "Motors/engine.h"

/**
 * @brief Constructs an Engine object.
 *
 * @param velocityPIN The pin number for controlling velocity. Needs analog pin.
 * @param positivePIN The pin number for forward direction. Needs digital pin.
 * @param negativePIN The pin number for backward direction. Needs digital pin.
 */
Engine::Engine(int velocityPIN, int positivePIN, int negativePIN)
{
    engineVelocityPIN = velocityPIN;
    enginePositivePIN = positivePIN;
    engineNegativePIN = negativePIN;
}

/**
 * @brief Reverses the direction of the engine.
 */
void Engine::directionReverse()
{
    if (direction)
    {
        digitalWrite(enginePositivePIN, LOW);
        digitalWrite(engineNegativePIN, HIGH);
    }
    else
    {
        digitalWrite(enginePositivePIN, HIGH);
        digitalWrite(engineNegativePIN, LOW);
    }
}

/**
 * @brief Sets the velocity of the engine.
 *
 * @param newVelocity The new velocity to set, rescaled using the Arduino
 * map function to the desired range for the engine.
 * @param obstacle Indicates if there is an obstacle in the way (true if obstacle present,
 * false otherwise). If true, the engine should hinder forward movement.
 */
void Engine::setVelocity(int inVelocity, bool obsticle)
{
    int newVelocity = map(inVelocity, 0, 4096, -255, 255);

    if (newVelocity == currentVelocity)
    {
        return;
    }
    else
    {
        currentVelocity = newVelocity;
    }

    if ((newVelocity > -50) && (newVelocity < 20)) // Because of the hardware used there is a need for stabilizing
    {                                              // of the numbers recieved from the method call
        newVelocity = 0;
    }

    if (obsticle && (newVelocity > 0))
    {
        newVelocity = 0;
    }

    if (newVelocity < 0)
    {
        if (direction)
        {
            directionReverse();
            direction = false;
        }
    }
    else if (newVelocity > 0)
    {
        if (!direction)
        {
            directionReverse();
            direction = true;
        }
    }
    analogWrite(engineVelocityPIN, abs(newVelocity));
}

/**
 * @brief Initializes the engine.
 */
void Engine::intitateEngine()
{
    pinMode(engineVelocityPIN, OUTPUT);
    pinMode(enginePositivePIN, OUTPUT);
    pinMode(engineNegativePIN, OUTPUT);
    digitalWrite(enginePositivePIN, HIGH);
    digitalWrite(engineNegativePIN, LOW);
}