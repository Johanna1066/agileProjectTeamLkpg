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

    void initiateJoystick()
    {
        pinMode(joyStickVerticalPIN, INPUT);
        pinMode(joyStickHorizontalPIN, INPUT);
        pinMode(joyStickButtonPIN, INPUT);

        centerHorizontalValue = analogRead(joyStickHorizontalPIN);
        centerVerticalValue = analogRead(joyStickVerticalPIN);
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
            Serial.printf("joystick:verticalRead Y axis < centerVerticalValue. \nY = %d \n", verticalValue);
        }
        else if(centerVerticalValue < verticalValue)
        {
            Serial.printf("joystick:verticalRead Y axis > centerVerticalValue. \nY = %d \n", verticalValue);
        }
    }

    void horizontalRead()
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

    void buttonRead()
    {
        //TODO: if we use the button on Joystick
    }

    // IDEA: Setup subscription function
};