#pragma once
#include <ESP32Servo.h>


class SteeringServo
{
private:
    int direction{};
    int servoPIN{};

    Servo myServo;

public:
    SteeringServo(int engineServoPIN);

    ~SteeringServo();

    void initiateServo();

    void setDirection(int newDirection);
};

    SteeringServo::SteeringServo(int engineServoPIN)
    {
        servoPIN = engineServoPIN;
    }

    SteeringServo::~SteeringServo()
    {
        // delete direction;
    }

    void SteeringServo::initiateServo()
    {
        myServo.attach(servoPIN);
        myServo.write(60);
        myServo.setPeriodHertz(50);
    }

    void SteeringServo::setDirection(int newDirection)
    {
        // IDEA: Decide velocity by moving the pointer in tiny steps with delay??
        myServo.write(newDirection);


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