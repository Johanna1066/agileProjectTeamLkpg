#pragma once

class Motor
{
private:
public:
    void forwardData();
};

void Motor::forwardData()
{
}

//----------Engine class---------------

class Engine : public Motor
{
private:
    int engineVelocityAnalogPIN{};
    int enginePositiveDigitalPIN{};
    int engineNegativeDigitalPIN{};

    int velocity{};
    bool direction{}; // true = forward, false = backwards

public:
    Engine(int velocityPIN, int positivePIN, int negativePIN)
    {
        engineVelocityAnalogPIN = velocityPIN;
        enginePositiveDigitalPIN = positivePIN;
        engineNegativeDigitalPIN = negativePIN;

        pinMode(engineVelocityAnalogPIN, OUTPUT);
        pinMode(enginePositiveDigitalPIN, OUTPUT);
        pinMode(engineNegativeDigitalPIN, OUTPUT);
        digitalWrite(enginePositiveDigitalPIN, LOW);
        digitalWrite(engineNegativeDigitalPIN, HIGH);
    }

    ~Engine()
    {
        /*delete engineVelocityAnalogPIN;
        delete enginePositiveDigitalPIN;
        delete engineNegativeDigitalPIN;

        delete velocity;
        delete direction;*/
    }

    void setVelocity(int newVelocity)
    {
        analogWrite(engineVelocityAnalogPIN, newVelocity);
    }

    void directionReverse()
    {
        // May change depending on connection to enginedriver hardware
        // IDEA: add if- depending on bool diretion.

        digitalWrite(enginePositiveDigitalPIN, LOW);
        digitalWrite(engineNegativeDigitalPIN, HIGH);
    }
};

//---------Servo class---------------

class engineServo : public Motor
{
private:
    int direction{};

    Servo myServo;

public:
    engineServo(int engineServoPIN,int startDirection)
    {
        myServo.attach(engineServoPIN);
        myServo.write(startDirection);
    }

    ~engineServo()
    {
        // delete direction;
    }

    void setDirection(int newDirection)
    {
        // IDEA: Decide velocity by moving the pointer in tiny steps with delay??
        myServo.write(newDirection);
        direction = newDirection;


        /*
        Maybe something like this to move turning in tiny steps

        int currentPosition = myServo.read();

        if(newDirection > direction && minTurn > direction)
        {
            direction--;
            myServo.write(direction);
            delay(10;)
        }
        if else(newDirection < direction && maxTurn < direction)
        {
            direction++;
            myServo.write(direction);
            delay(10);
        }
        */
    }
};