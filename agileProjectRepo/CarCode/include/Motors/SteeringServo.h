class SteeringServo

{
private:
    // TODO: Add PINs
    int direction{};

public:
    SteeringServo()
    {
    }

    ~SteeringServo()
    {
        // delete direction;
    }

    void setDirection(int newDirection)
    {
        // IDEA: Decide velocity by moving the pointer in tiny steps with delay??
    }
};
