namespace okej
{
    std::vector<Engine> engines;
    Engine right(A1, D5, D6);
    Engine left(A2, D3, D4);
    SemaphoreHandle_t engineHandle;

    SteeringServo myServo(9);
    const int safeServoDistance{20};
    SemaphoreHandle_t servoHandle;

    USsensor mySensor(D8, D7); // TODO: Change to correct PINs
    bool hinderForwardMovement = false;

    int reading{};
    int dataRecieved{};

} // namespace name
