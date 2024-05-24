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

    int centerHorizontalValue{};
    int centerVerticalValue{};

public:
    Joystick(int verticalPIN, int horizontalPIN, int buttonPIN);

    ~Joystick();

    void initiateJoystick();

    void vertialRead();

    void horizontalRead();

    //void buttonRead();   If we are going to use button on joystick

};

Joystick::Joystick(int verticalPIN, int horizontalPIN, int buttonPIN)
{
    joyStickVerticalPIN = verticalPIN;
    joyStickHorizontalPIN = horizontalPIN;
    joyStickButtonPIN = buttonPIN;
    this->initiateJoystick();
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

    centerHorizontalValue = analogRead(joyStickHorizontalPIN);
    centerVerticalValue = analogRead(joyStickVerticalPIN);
}

void Joystick::vertialRead()
{
    verticalValue = analogRead(joyStickVerticalPIN);

    if((centerVerticalValue - 100) <= verticalValue && verticalValue <= (centerVerticalValue + 100))
    {
        Serial.println("joystick:verticalRead Y axis center.");
    }
    else if(centerVerticalValue > verticalValue)
    {
        Serial.printf("joystick:verticalRead Y axis < centerVerticalValue. \nY = %d \n", verticalValue);
    }
    else if(centerVerticalValue < verticalValue)
    {
        Serial.printf("joystick:verticalRead Y axis > centerVerticalValue. \nY = %d \n", verticalValue);
    }
}

void Joystick::horizontalRead()
{
    horizontalValue = analogRead(joyStickHorizontalPIN);

    if((centerHorizontalValue - 100) <= horizontalValue && horizontalValue <= (centerHorizontalValue + 100))
    {
        Serial.println("joystick:horizontalRead X axis center.");
    }
    else if(centerHorizontalValue > horizontalValue)
    {
        Serial.printf("joystick:horizontalRead X axis < centerHorizontalValue. \nX = %d \n", horizontalValue);
    }
    else if(centerHorizontalValue < horizontalValue)
    {
        Serial.printf("joystick:horizontalRead X axis > centerHorizontalValue. \nX = %d \n", horizontalValue);
    }
}

/*Joystick::buttonRead()
    {
        //TODO: if we use the button on Joystick
    }*/