/*
 * Engine.cpp
 */

#include <Arduino.h>
#include "Motors/Engine.h"

Engine::Engine(int velocityPIN, int positivePIN, int negativePIN)
{
    engineVelocityPIN = velocityPIN;
    enginePositivePIN = positivePIN;
    engineNegativePIN = negativePIN;
}

Engine::~Engine()
{
}

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

void Engine::intitateEngine()
{
    pinMode(engineVelocityPIN, OUTPUT);
    pinMode(enginePositivePIN, OUTPUT);
    pinMode(engineNegativePIN, OUTPUT);
    digitalWrite(enginePositivePIN, HIGH);
    digitalWrite(engineNegativePIN, LOW);
}