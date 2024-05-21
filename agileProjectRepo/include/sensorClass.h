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

        distance = (messurement / 2) / 29.1; // Convert distance to cm
    }

    // IDEA: Setup subscription function
};

//------Joystick---------


class joystick : public Sensor
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
    joystick(int verticalPIN, int horizontalPIN, int buttonPIN)
    {
        joyStickVerticalPIN = verticalPIN;
        joyStickHorizontalPIN = horizontalPIN;
        joyStickButtonPIN = buttonPIN;
    }


    ~joystick()
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

    void joystickInitiate()
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

        return; //tmp for task

        if((centerVerticalValue - 100) <= verticalValue && verticalValue <= (centerVerticalValue + 100))
        {
            //Serial.println("joystick:verticalRead Y axis center.");
        }
        else if(centerVerticalValue > verticalValue)
        {
            //Serial.printf("joystick:verticalRead Y axis < centerVerticalValue. \nY = %d \n", verticalValue);
        }
        else if(centerVerticalValue < verticalValue)
        {
            //Serial.printf("joystick:verticalRead Y axis > centerVerticalValue. \nY = %d \n", verticalValue);
        }
    }

    void horizontalRead()
    {
        horizontalValue = analogRead(joyStickVerticalPIN);

        return; //tmp for task

        if((centerHorizontalValue - 100) <= horizontalValue && horizontalValue <= (centerHorizontalValue + 100))
        {
            //Serial.println("joystick:verticalRead Y axis center.");
        }
        else if(centerHorizontalValue > horizontalValue)
        {
            //Serial.printf("joystick:verticalRead Y axis < centerHorizontalValue. \nY = %d \n", horizontalValue);
        }
        else if(centerHorizontalValue < horizontalValue)
        {
            //Serial.printf("joystick:verticalRead Y axis > centerHorizontalValue. \nY = %d \n", horizontalValue);
        }
    }

    int getHorizontalValue()
    {
        return horizontalValue;
    }

    int getVerticalValue()
    {
        return verticalValue;
    }

    void buttonRead()
    {
        //TODO: if we use the button on Joystick
    }

    // IDEA: Setup subscription function
};