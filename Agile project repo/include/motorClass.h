#pragma once

class Motor
{
private:
public:
    void forwardData();
};

void Motor::forwardData()
{
}

//----------Engine class---------------

class Engine : public Motor
{
private:
#define engingeRightVelocity A1 // The Arduino Nano ESP32 pin connected to the ENA pin L298N
#define engingeRightPositive D6 // The Arduino Nano ESP32 pin connected to the IN1 pin L298N
#define engingeRightNegative D5
#define engineLeftVelocity A2
#define engingeLeftPositive D4
#define engingeLeftNegative D3

    int velocity{};
    bool direction{}; // true = forward, false = backwards

public:
    void setVelocity(int newVelocity);
    void initiateEngine();
    void directionReverse();
};

Engine::Engine()
{
}

Engine::~Engine()
{
}

void intitateEngine()
{
    pinMode(engingeRightVelocity, OUTPUT);
    pinMode(engingeRightPositive, OUTPUT);
    pinMode(engingeRightNegative, OUTPUT);
    pinMode(engineLeftVelocity, OUTPUT);
    pinMode(engingeLeftPositive, OUTPUT);
    pinMode(engingeLeftNegative, OUTPUT);
}

void directionReverse()
{
    // May change depending on connection to enginedriver hardware
    // IDEA: add if- depending on bool diretion.

    digitalWrite(engingeRightPositive, LOW);
    digitalWrite(engingeRightNegative, HIGH);

    digitalWrite(engingeLeftPositive, LOW);
    digitalWrite(engingeLeftNegative, HIGH);
}

//---------Servo class---------------

class Servo : public Motor
{
private:
    int direction{};

public:
    Servo::Servo();
    Servo::~Servo();
    void setDirection(int newDirection);
};

Servo::Servo()
{
}
Servo::~Servo()
{
}

void setDirection(int newDirection)
{
    // IDEA: Decide velocity by moving the pointer in tiny steps with delay??
}