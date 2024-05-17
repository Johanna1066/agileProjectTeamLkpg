#pragma once

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
    int sensorTriggerDigitalPIN;
    int sensorRecieverDigitalPIN;

    int distance{};

public:
    USsensor::USsensor(int triggerPIN, int recieverPIN)
    {
        sensorTriggerDigitalPIN = triggerPIN;
        sensorRecieverDigitalPIN = recieverPIN;
    }

    USsensor::~USsensor()
    {
        delete sensorTriggerDigitalPIN;
        delete sensorRecieverDigitalPIN;

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
    int joyStickVerticalAnalogPIN;
    int joyStickHorizontalAnalogPIN;
    int joyStickButtonDigitalPIN;

    int verticalValue{};
    int horizontalValue{};
    int buttonValue{};

public:
    joyStick::joyStick(int verticalPIN, int horizontalPIN, int buttonPIN)
    {
        joyStickVerticalAnalogPIN = verticalPIN;
        joyStickHorizontalAnalogPIN = horizontalPIN;
        joyStickButtonDigitalPIN = buttonPIN;
    }

    joyStick::~joyStick()
    {
        /*
        delete joyStickButtonDigitalPIN;
        delete joyStickHorizontalAnalogPIN;
        delete joyStickButtonDigitalPIN;

        delete verticalValue;
        delete horizontalValue;
        delete buttonValue;
        */
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
