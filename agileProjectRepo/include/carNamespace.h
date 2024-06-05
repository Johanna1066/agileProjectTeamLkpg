#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <vector>


namespace globalVariables
{
    std::vector<Engine> engines;
    Engine right(A1, D5, D6);
    Engine left(A2, D3, D4);
    SemaphoreHandle_t engineHandle;

    SteeringServo myServo(9);
    const int safeServoDistance{20};
    SemaphoreHandle_t servoHandle;

    USsensor mySensor(D8, D7);
    bool hinderForwardMovement = false;

    int reading{};
    int dataRecieved{};

} // namespace globalVariables
