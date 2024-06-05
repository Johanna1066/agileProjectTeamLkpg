#include <Arduino.h>
#include "Sensors/joystick.h"

/*
 * @brief Constructor that initializes joystickAnalogPIN with the provided pin number
 * @param pinIN the analog pin number to which the joystick is connected
 */
Joystick::Joystick(int pinIN)
{
    joystickAnalogPIN = pinIN;
}


/*
 * @brief Initializes the joystick by setting the pin mode and reading the initial center value
 */
void Joystick::initiateJoystick()
{
    pinMode(joystickAnalogPIN, INPUT);
    initialCenter = analogRead(joystickAnalogPIN);
}

/*
 * @brief Reads the joystick value and updates currentValue after remapping it
 */
void Joystick::doReading()
{
    int read = analogRead(joystickAnalogPIN);

    if (read <= initialCenter)
    {
        currentValue = map(read, 0, initialCenter, 0, 2048);
    }
    else
    {
        currentValue = map(read, initialCenter, 4096, 2049, 4096);
    }
}

/*
 * @brief Returns the current value of the joystick after remapping
 */
int Joystick::getValue()
{
    return currentValue;
}
