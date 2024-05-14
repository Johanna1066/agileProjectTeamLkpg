#pragma once

class Controller
{
private:
public:
};

//--------AntiCrash------------

/*IDEA: have high priority in RTOS*/

class AntiCrash : public Controller
{
private:
    int distanceToObject{};
    int minSafetyDistance{};
    int maxSafetyDistance{};

public:
    AntiCrash::AntiCrash();
    AntiCrash::~AntiCrash();
    void checkDistance(int newReading);
};
AntiCrash::AntiCrash()
{
}

AntiCrash::~AntiCrash()
{
}

void checkDistance(int newReading)
{
}

//-------Steering----------

class Steering : public Controller
{
private:
    int engineVelocity{};
    bool engingeDirection{};
    int servoDirection{};

public:
    Steering::Steering();
    Steering::~Steering();
    void updateEngineVelocity(int newReading);
    void updateEngineDirection();
    void updateServoDirection(int newReading);
};
Steering::Steering()
{
}
Steering::~Steering()
{
}

void updateEngineVelocity(int newReading)
{

    // IDEA: Map new reading with posible velocities
    // IDEA: Update engineVeclocity
}

void updateEngineDirection()
{
}

void updateServoDIrection(int newReading)
{

    // IDEA: Map new reading with posible directions
    // IDEA: Update servoDIrection
}
