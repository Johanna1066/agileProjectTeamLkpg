#pragma once

class Controller
{
private:
public:
    Controller(/* args */);
    ~Controller();
    void forwardData();
};

Controller::Controller(/* args */)
{
}

Controller::~Controller()
{
}

void Controller::forwardData()
{
}

//----------Engine class---------------

class Engine : public Controller
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

Engine::Engine()
{
}

Engine::~Engine()
{
}

//---------Servo class---------------

class servo : public Controller
{
private:
    int direction{};

public:
    void setDirection(int newDirection);
};

void setDirection(int newDirection)
{
    // IDEA: Decide velocity by moving the pointer in tiny steps with delay??
}