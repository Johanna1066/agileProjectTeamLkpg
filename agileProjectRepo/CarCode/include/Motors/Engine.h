#pragma once

class Engine
{
private:
    int engineVelocityPIN{};
    int enginePositivePIN{};
    int engineNegativePIN{};

    int velocity{};
    bool direction{}; // true = forward, false = backwards

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

void Engine::setVelocity(int newVelocity)
{
    analogWrite(engineVelocityPIN, newVelocity);
}

void Engine::intitateEngine()
{
    pinMode(engineVelocityPIN, OUTPUT);
    pinMode(enginePositivePIN, OUTPUT);
    pinMode(engineNegativePIN, OUTPUT);
    digitalWrite(enginePositivePIN, LOW);
    digitalWrite(engineNegativePIN, HIGH);
}
void Engine::directionReverse()
{
    // May change depending on connection to enginedriver hardware
    // IDEA: add if- depending on bool diretion.

    digitalWrite(enginePositivePIN, LOW);
    digitalWrite(engineNegativePIN, HIGH);
}


