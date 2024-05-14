#pragma once
/*
class Sensor
{
private:

public:
    Sensor();
    ~Sensor();
};

//------USSensor---------

class USsensor : public Sensor
{
private:
    int sensorTriggerPIN;
    int sensorRecieverPIN;

    int distance{};

public:
    USsensor::USsensor(int triggerPIN, int recieverPIN)
    {
        sensorTriggerPIN = triggerPIN;
        sensorRecieverPIN = recieverPIN;
    }

    USsensor::~USsensor()
    {
        delete sensorTriggerPIN;
        delete sensorRecieverPIN;

        delete distance;
    }

    void setDistance()
    {
    }

    void initiateSensor()
    {
    }

    void readDistance()
    {
    }

    // IDEA: Setup subscription function
};

//------Joystick---------

class joyStick : public Sensor
{
private:
    int joyStickVerticalPIN;
    int joyStickHorizontalPIN;
    int joyStickButtonPIN;

    int verticalValue{};
    int horizontalValue{};
    int buttonValue{};

public:
    joyStick::joyStick(int verticalPIN, int horizontalPIN, int buttonPIN)
    {
        joyStickVerticalPIN = verticalPIN;
        joyStickHorizontalPIN = horizontalPIN;
        joyStickButtonPIN = buttonPIN;
    }

    joyStick::~joyStick()
    {
        delete joyStickButtonPIN;
        delete joyStickHorizontalPIN;
        delete joyStickButtonPIN;

        delete verticalValue;
        delete horizontalValue;
        delete buttonValue;
    }

    void vertialRead()
    {
    }

    void horizontalRead()
    {
    }

    void buttonRead()
    {
    }

    // IDEA: Setup subscription function
};
*/
