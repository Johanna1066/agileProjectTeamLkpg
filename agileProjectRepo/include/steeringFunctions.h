#pragma once

std::vector<Engine> engines;

Engine right(A1, D6, D5);
Engine left(A2, D4, D3);

SteeringServo myServo(9);

USsensor mySensor(D9, D10); // TODO: Change to correct PINs

int reading{};
int dataRecieved{};

int engineSpeed{};
uint8_t direction{};
bool hinderForwardMovement = false;

void initiate()
{
    myServo.initiateServo();
    engines.push_back(left);
    engines.push_back(right);
    right.intitateEngine();
    left.intitateEngine();
    // mySensor.initiateUSsensor();
}
void stopEngines()
{
    for (auto &engine : engines)
    {
        engine.setVelocity(0);
    }
}

void setEnginesVelocity(int velocity)
{
    for (auto &engine : engines)
    {
        engine.setVelocity(velocity);
    }
}