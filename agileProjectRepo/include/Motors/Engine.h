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

    // Serial.printf("New newVelocity = %d \n", inVelocity);
    // Serial.printf("newVelocity = %d\n", newVelocity);
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
