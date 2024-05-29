#pragma once

class Engine
{
private:
    int engineVelocityPIN{};
    int enginePositivePIN{};
    int engineNegativePIN{};

    int newVelocity{};
    bool direction{true}; // true = forward, false = backwards

public:
    Engine(int velocityPIN, int positivePIN, int negativePIN);
    ~Engine();
    void setVelocity(int);
    void intitateEngine();
    void directionReverse();
};

Engine::Engine(int velocityPIN, int positivePIN, int negativePIN)
{
    engineVelocityPIN = velocityPIN;
    enginePositivePIN = positivePIN;
    engineNegativePIN = negativePIN;
    this->intitateEngine();
}

Engine::~Engine()
{
}

void Engine::directionReverse()
{
    // May change depending on connection to enginedriver hardware
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

void Engine::setVelocity(int inVelocity)
{
    int newVelocity = map(inVelocity, 0, 4096, -255, 255);

    if ((newVelocity > -20) && (newVelocity < 20))
    {
        newVelocity = 0;
    }

    //Serial.printf("New newVelocity = %d \n", inVelocity);
    //Serial.printf("Velocity = %d\n", newVelocity);
    if (inVelocity < 0)
    {
        if (direction)
        {
            directionReverse();
            direction = false;
        }
    }
    else if (inVelocity > 0)
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
    digitalWrite(enginePositivePIN, LOW);
    digitalWrite(engineNegativePIN, HIGH);
}
