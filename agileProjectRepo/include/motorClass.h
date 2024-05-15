#pragma once
#include <engineServo.h>

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
    int engineVelocityPIN{};
    int enginePositivePIN{};
    int engineNegativePIN{};

    int velocity{};
    bool direction{}; // true = forward, false = backwards

public:
    Engine(int velocityPIN, int positivePIN, int negativePIN)
    {
        engineVelocityPIN = velocityPIN;
        enginePositivePIN = positivePIN;
        engineNegativePIN = negativePIN;
    }

    ~Engine()
    {
        /*delete engineVelocityPIN;
        delete enginePositivePIN;
        delete engineNegativePIN;

        delete velocity;
        delete direction;*/
    }

    void setVelocity(int newVelocity)
    {
        analogWrite(engineVelocityPIN, newVelocity);
    }

    void intitateEngine()
    {
        pinMode(engineVelocityPIN, OUTPUT);
        pinMode(enginePositivePIN, OUTPUT);
        pinMode(engineNegativePIN, OUTPUT);
        digitalWrite(enginePositivePIN, LOW);
        digitalWrite(engineNegativePIN, HIGH);
    }
    void directionReverse()
    {
        // May change depending on connection to enginedriver hardware
        // IDEA: add if- depending on bool diretion.

        digitalWrite(enginePositivePIN, LOW);
        digitalWrite(engineNegativePIN, HIGH);
    }
};

//---------engineServo class---------------

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
