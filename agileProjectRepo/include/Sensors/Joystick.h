#pragma once
//------Joystick---------

// enumeration to decide wich type the joystick object is

class Joystick
{
private:
    int joystickPIN{};
    int value{};

    int center{};

public:
    Joystick(int pinIN);

    ~Joystick();

    void initiateJoystick();

    void doReading();

    int getValue();
};

Joystick::Joystick(int pinIN)
{
    joystickPIN = pinIN;
}

Joystick::~Joystick()
{
}

void Joystick::initiateJoystick()
{
    pinMode(joystickPIN, INPUT);
    center = analogRead(joystickPIN); // TODO: kalibrera om genom att trycka på knappen?
}

void Joystick::doReading()
{
    int read = analogRead(joystickPIN);

    if (read <= center)
    {
        value = map(read, 0, center, 0, 2048);
    }
    else
    {
        value = map(read, center, 4095, 2049, 4095);
    }
}

int Joystick::getValue()
{
    return value;
}
