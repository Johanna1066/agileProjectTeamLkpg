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
    int sensorTriggerDigitalPIN;
    int sensorRecieverDigitalPIN;

    long distance{};
    long messurement{};

public:
    USsensor(int triggerPIN, int recieverPIN)
    {
        sensorTriggerDigitalPIN = triggerPIN;
        sensorRecieverDigitalPIN = recieverPIN;
        
    }

    void USsensorInitiate()
    {
        pinMode(sensorTriggerDigitalPIN, OUTPUT);
        pinMode(sensorRecieverDigitalPIN, INPUT);
    }

    ~USsensor()
    {
        /*
        delete sensorTriggerDigitalPIN;
        delete sensorRecieverDigitalPIN;

        delete distance;
        */
    }

    long getDistance()
    {
        return distance;
    }


    void readDistance()
    {
        digitalWrite(sensorTriggerDigitalPIN, LOW);
        delay(5);
        digitalWrite(sensorTriggerDigitalPIN, HIGH);
        delay(10);
        digitalWrite(sensorTriggerDigitalPIN, LOW);

        pinMode(sensorRecieverDigitalPIN, INPUT);

        messurement = pulseIn(sensorRecieverDigitalPIN, HIGH);

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

    int centerHorizontalValue{};
    int centerVerticalValue{};

public:
    joyStick(int verticalPIN, int horizontalPIN, int buttonPIN)
    {
        joyStickVerticalPIN = verticalPIN;
        joyStickHorizontalPIN = horizontalPIN;
        joyStickButtonPIN = buttonPIN;

        pinMode(joyStickVerticalPIN, INPUT);
        pinMode(joyStickHorizontalPIN, INPUT);
        pinMode(joyStickButtonPIN, INPUT);

        centerHorizontalValue = analogRead(joyStickHorizontalPIN);
        centerVerticalValue = analogRead(joyStickVerticalPIN);
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
        verticalValue = analogRead(joyStickVerticalPIN);

        if((centerVerticalValue - 100) <= verticalValue && verticalValue <= (centerVerticalValue + 100))
        {
            Serial.println("joystick:verticalRead Y axis center.");
        }
        else if(centerVerticalValue > verticalValue)
        {
            Serial.println("joystick:verticalRead Y axis < centerVerticalValue. \nY = %d", verticalValue);
        }
        else if(centerVerticalValue < verticalValue)
        {
            Serial.println("joystick:verticalRead Y axis > centerVerticalValue. \nY = %d", verticalValue);
        }
    }

    void horizontalRead()
    {
        //Copy paste from vertical read and remake to fit horizontal
    }

    void buttonRead()
    {
        //TODO: if we use the button on Joystick
    }

    // IDEA: Setup subscription function
};