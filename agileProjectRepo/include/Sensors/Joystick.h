#ifndef _WCC_JOYSTICK_H
#define _WCC_JOYSTICK_H
/*
 * @brief Joystick class
 * Each object of the Joystick class controls one joystick direction.
 *
 * The default constructor Joystick(int) requires an Arduino PIN to function.
 * This allows the Joystick to read and get values from the joystick.
 *
 * Joystick has 3 methods: initiateJoystick(), doReading(), and getValue()
 *
 * Joystick has 3 private variables: joystickAnalogPIN, currentValue, and initialCenter
 */
class Joystick
{
private:
    // @brief used in initiateJoystick. Gets its value from the constructor Joystick(int PIN)
    int joystickAnalogPIN{};

    // @brief stores the joystick's current value, updated in doReading()
    int currentValue{};

    // @brief used to find and map the center value of the joystick
    int initialCenter{};
public:
    Joystick(int pinIN);


    ~Joystick() = default;

    void initiateJoystick();

    void doReading();

    int getValue();
};
#endif //_WCC_JOYSTICK_H
