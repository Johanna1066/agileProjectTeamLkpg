#pragma once

class SteeringServo
{
private:
    int direction{60};
    int servoPIN{};

    Servo servoObject;

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
    servoObject.attach(servoPIN);
    servoObject.write(60);
    servoObject.setPeriodHertz(50);
}

void SteeringServo::setDirection(int inDirection)
{
    int newDirection = map(inDirection, 0, 4096, 0, 120);
    // IDEA: Decide velocity by moving the pointer in tiny steps with delay??
    servoObject.write(newDirection);
}