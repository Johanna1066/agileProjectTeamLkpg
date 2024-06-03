#pragma once

std::vector<Engine> engines;

Engine right(A1, D5, D6);
Engine left(A2, D3, D4);

SteeringServo myServo(9);

USsensor mySensor(D8, D7); // TODO: Change to correct PINs

int reading{};
int safeServoDistance{20};
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
    mySensor.initiateUSsensor();
}

void setEnginesVelocity(int velocity, bool obsticle)
{
    for (auto &engine : engines)
    {
        engine.setVelocity(velocity, obsticle);
    }
}