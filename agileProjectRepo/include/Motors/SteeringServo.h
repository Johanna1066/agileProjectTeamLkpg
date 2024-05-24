#include <ESP32Servo.h>
#include "steeringFunctions.h"


class SteeringServo
{
private:
    int direction{};
    int servoPIN{};

    Servo myServo;

public:
    SteeringServo(int engineServoPIN)
    {
        servoPIN = engineServoPIN;
    }

    ~SteeringServo()
    {
        // delete direction;
    }

    void ServoInitiate()
    {
        myServo.attach(servoPIN);
       // myServo.setPeriodHertz(50);
    }

    void setDirection(int newDirection)
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
};