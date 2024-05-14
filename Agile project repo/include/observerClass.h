#pragma once

class Observer
{
private:
public:
    Observer(/* args */);
    ~Observer();
};

Observer::Observer(/* args */)
{
}

Observer::~Observer()
{
}

//--------AntiCrash------------

/*IDEA: have high priority in RTOS*/

class AntiCrash : public Observer
{
private:
    int distanceToObject{};
    int minSafetyDistance{};
    int maxSafetyDistance{};

public:
    void checkDistance(int newReading);
};

void checkDistance(int newReading)
{
}

//-------Steering----------

class Steering : public Observer
{
private:
    int engineVelocity{};
    bool engingeDirection{};
    int servoDirection{};

public:
    void updateEngineVelocity(int newReading);
    void updateEngineDirection();
    void updateServoDirection(int newReading);
};

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
