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
protected:
    int currentDistance{};
    int lastDistance{};
    int stopDistance{};


public:
    AntiCrash(int defaultStopDistance)
    {
        stopDistance = defaultStopDistance;
    }

    ~AntiCrash()
    {
        /*
        delete distanceToObject;
        delete minSafetyDistance;
        delete maxSafetyDistance;
        */
    }
    void updateDistance(int newDistance)
    {
        lastDistance = currentDistance;
        currentDistance = newDistance;
    }
};

class AntiCrashAhead : public AntiCrash
{
    private:
    public:
    bool stopVehicle()
    {
        if(lastDistance < stopDistance && currentDistance < stopDistance)
        {
            return true;
        }
        return false;
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