#pragma once

class Controller
{
private:
public:
};

//--------AntiCrash------------

//IDEA: have high priority in RTOS

class AntiCrash : public Controller
{
private:
    int distanceToObject{};
    int minSafetyDistance{};
    int maxSafetyDistance{};

public:
    AntiCrash()
    {
    }

    ~AntiCrash()
    {
        /*
        delete distanceToObject;
        delete minSafetyDistance;
        delete maxSafetyDistance;
        */
    }

    void checkDistance(int newReading)
    {
    }
};

//-------Steering----------

class Steering : public Controller
{
private:
    int engineVelocity{};
    bool engingeDirection{};
    int servoDirection{};

public:
    Steering()
    {
    }
    ~Steering()
    {
        /*
        delete engineVelocity;
        delete engingeDirection;
        delete servoDirection;
        */
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
};