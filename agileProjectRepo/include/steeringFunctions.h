#pragma once


std::vector<Engine> engines;

Engine right(A1, D6, D5);
Engine left(A2, D4, D3);

SteeringServo myServo(9);
Joystick stick(A1, A2, 3);

//USsensor mySensor(D9, D10);
long reading;
bool hinderForwardMovement = false;

void initiate()
{
    stick.initiateJoystick();
    myServo.initiateServo();
    engines.push_back(left);
    engines.push_back(right);
    right.intitateEngine();
    left.intitateEngine();
    //mySensor.initiateUSsensor();


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