#pragma once

class Sensor
{
private:

public:
    
};

//------USSensor---------

class USsensor : public Sensor
{
private:
    int sensorTriggerPIN;
    int sensorRecieverPIN;

    long distance{};
    long messurement{};

public:
    USsensor(int triggerPIN, int recieverPIN)
    {
        sensorTriggerPIN = triggerPIN;
        sensorRecieverPIN = recieverPIN;
        
    }

    void USsensorInitiate()
    {
        pinMode(sensorTriggerPIN, OUTPUT);
        pinMode(sensorRecieverPIN, INPUT);
    }

    ~USsensor()
    {
        /*
        delete sensorTriggerPIN;
        delete sensorRecieverPIN;

        delete distance;
        */
    }

    long getDistance()
    {
        return distance;
    }


    void readDistance()
    {
        digitalWrite(sensorTriggerPIN, LOW);
        delay(5);
        digitalWrite(sensorTriggerPIN, HIGH);
        delay(10);
        digitalWrite(sensorTriggerPIN, LOW);

        pinMode(sensorRecieverPIN, INPUT);

        messurement = pulseIn(sensorRecieverPIN, HIGH);

        distance = (messurement / 2) / 29.1;   //Convert distance to cm
    }



    // IDEA: Setup subscription function
};

//------Joystick---------

class joyStick : public Sensor
{
private:
    int joyStickVerticalPIN{};
    int joyStickHorizontalPIN{};
    int joyStickButtonPIN{};

    int verticalValue{};
    int horizontalValue{};
    int buttonValue{};

public:
    joyStick(int verticalPIN, int horizontalPIN, int buttonPIN)
    {
        joyStickVerticalPIN = verticalPIN;
        joyStickHorizontalPIN = horizontalPIN;
        joyStickButtonPIN = buttonPIN;
    }

    ~joyStick()
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