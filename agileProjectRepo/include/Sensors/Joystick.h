#pragma once
//------Joystick---------

class Joystick
{
private:
    int joyStickVerticalPIN{};
    int joyStickHorizontalPIN{};
    int joyStickButtonPIN{};

    int verticalValue{};
    int horizontalValue{};
    int buttonValue{};

public:
    Joystick(int verticalPIN, int horizontalPIN, int buttonPIN);

    ~Joystick();

    void initiateJoystick();

    void verticalRead();

    void horizontalRead();

    int getHorizontalValue();

    int getVerticalValue();

    // void buttonRead();   If we are going to use button on joystick
};

Joystick::Joystick(int verticalPIN, int horizontalPIN, int buttonPIN)
{
    joyStickVerticalPIN = verticalPIN;
    joyStickHorizontalPIN = horizontalPIN;
    joyStickButtonPIN = buttonPIN;
}

Joystick::~Joystick()
{
    /*
    delete joyStickButtonPIN;
    delete joyStickHorizontalPIN;
    delete joyStickButtonPIN;

    delete verticalValue;
    delete horizontalValue;
    delete buttonValue;
    */
}

void Joystick::initiateJoystick()
{
    pinMode(joyStickVerticalPIN, INPUT);
    pinMode(joyStickHorizontalPIN, INPUT);
    pinMode(joyStickButtonPIN, INPUT);

}

void Joystick::verticalRead()
{
    verticalValue = analogRead(joyStickVerticalPIN);
    // Serial.printf("Value = %d\n", verticalValue);
}

void Joystick::horizontalRead()
{
    horizontalValue = analogRead(joyStickHorizontalPIN);
}

int Joystick::getHorizontalValue()
{
    // Serial.println(horizontalValue);
    return horizontalValue;
}

int Joystick::getVerticalValue()
{
    return verticalValue;
}

/*Joystick::buttonRead()
    {
        //TODO: if we use the button on Joystick
    }*/