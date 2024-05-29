#pragma once


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

    void SteeringServo::setDirection(int inDirection)
    {
        int newDirection = map(inDirection, 0, 4096, 0, 120);
        // IDEA: Decide velocity by moving the pointer in tiny steps with delay??
        myServo.write(newDirection);
    }