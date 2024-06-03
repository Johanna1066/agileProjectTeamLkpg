#pragma once

/*
The Engine class is responsible for controlling the speed of the engines.
The members engineVelocityPIN, enginePositivePIN and engineNegativePIN are
the hardware connection and need to be initiated when an engine object is created.

The bool direction keeps track if the engine is currently going backwards or forward.

The class has three methods; setVelocity - takes two arguments, the int inVelocity that
                                           should be the desired new velocity for the engine,
                                           and the bool obsticle that should be true of there is
                                           an obsticle in the way and the engine shoul hinder
                                           movement forwards.
                             directionReverse -

*/

class Engine
{
private:
    int engineVelocityPIN{};
    int enginePositivePIN{};
    int engineNegativePIN{};

    bool direction{true}; // true = forward, false = backwards

public:
    Engine(int velocityPIN, int positivePIN, int negativePIN);
    ~Engine();
    void setVelocity(int, bool);
    void intitateEngine();
    void directionReverse();
};

Engine::Engine(int velocityPIN, int positivePIN, int negativePIN)
{
    engineVelocityPIN = velocityPIN;
    enginePositivePIN = positivePIN;
    engineNegativePIN = negativePIN;
}

Engine::~Engine()
{
}

void Engine::directionReverse()
{
    if (direction)
    {
        digitalWrite(enginePositivePIN, LOW);
        digitalWrite(engineNegativePIN, HIGH);
    }
    else
    {
        digitalWrite(enginePositivePIN, HIGH);
        digitalWrite(engineNegativePIN, LOW);
    }
}

void Engine::setVelocity(int inVelocity, bool obsticle)
{
    int newVelocity = map(inVelocity, 0, 4096, -255, 255);

    if ((newVelocity > -50) && (newVelocity < 20))
    {
        newVelocity = 0;
    }

    if (obsticle && (newVelocity > 0))
    {
        newVelocity = 0;
    }

    if (newVelocity < 0)
    {
        if (direction)
        {
            directionReverse();
            direction = false;
        }
    }
    else if (newVelocity > 0)
    {
        if (!direction)
        {
            directionReverse();
            direction = true;
        }
    }
    analogWrite(engineVelocityPIN, abs(newVelocity));
}

void Engine::intitateEngine()
{
    pinMode(engineVelocityPIN, OUTPUT);
    pinMode(enginePositivePIN, OUTPUT);
    pinMode(engineNegativePIN, OUTPUT);
    digitalWrite(enginePositivePIN, HIGH);
    digitalWrite(engineNegativePIN, LOW);
}