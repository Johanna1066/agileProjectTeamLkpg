#include <Arduino.h>
#include "Sensors/Joystick.h"

Joystick::Joystick(int pinIN)
{
    joystickAnalogPIN = pinIN;
}

Joystick::~Joystick()
{
}

void Joystick::initiateJoystick()
{
    pinMode(joystickAnalogPIN, INPUT);
    initialCenter = analogRead(joystickAnalogPIN);
}

void Joystick::doReading()
{
    int read = analogRead(joystickAnalogPIN);

    if (read <= initialCenter)
    {
        currentValue = map(read, 0, initialCenter, 0, 2048);
    }
    else
    {
        currentValue = map(read, initialCenter, 4095, 2049, 4095);
    }
}

int Joystick::getValue()
{
    return currentValue;
}