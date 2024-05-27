#pragma once

class Engine
{
private:
    int engineVelocityPIN{};
    int enginePositivePIN{};
    int engineNegativePIN{};

    int velocity{};
    bool direction{true}; // true = forward, false = backwards

public:
    Engine(int velocityPIN, int positivePIN, int negativePIN);
    ~Engine();
    void setVelocity(int newVelocity);
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

void Engine::setVelocity(int newVelocity)
{
    int velocity = map(newVelocity, 0, 4096, -255, 255);

    if ((velocity > -20) && (velocity < 20))
    {
        velocity = 0;
    }

    Serial.printf("New velocity = %d \n", newVelocity);
    Serial.printf("Velocity = %d\n", velocity);
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
    analogWrite(engineVelocityPIN, abs(velocity));
}

void Engine::intitateEngine()
{
    pinMode(engineVelocityPIN, OUTPUT);
    pinMode(enginePositivePIN, OUTPUT);
    pinMode(engineNegativePIN, OUTPUT);
    digitalWrite(enginePositivePIN, LOW);
    digitalWrite(engineNegativePIN, HIGH);
}
