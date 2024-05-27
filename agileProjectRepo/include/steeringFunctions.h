#pragma once


std::vector<Engine> engines;

Engine right(A1, D6, D5);
Engine left(A2, D4, D3);

SteeringServo myServo(9);
Joystick verticalJoystick(A6, A1, 12);  //Använder A6
Joystick horizontalJoystick(A1, A2, 12);  //Använder A2

//USsensor mySensor(D9, D10);
int reading{};
int engineSpeed{};
bool hinderForwardMovement = false;

void initiate()
{
    verticalJoystick.initiateJoystick();
    horizontalJoystick.initiateJoystick();
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