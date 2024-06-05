#include <vector>

namespace globalVariables
{
    std::vector<Engine> engines;
    Engine rightEngine(A1, D5, D6);
    Engine leftEngine(A2, D3, D4);
    SemaphoreHandle_t engineHandle;

    SteeringServo servo(9);
    const int safeServoDistance{20};
    SemaphoreHandle_t servoHandle;

    USsensor sensor(D8, D7);
    bool hinderForwardMovement = false;

    int reading{};
    int dataRecieved{};

}
