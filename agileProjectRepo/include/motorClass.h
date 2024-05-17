//----------Engine class---------------

class Engine
{
private:
    int engineVelocityPIN{};
    int enginePositivePIN{};
    int engineNegativePIN{};

    int velocity{};
    bool direction{}; // true = forward, false = backwards

public:
    Engine(int velocityPIN, int positivePIN, int negativePIN)
    {
        engineVelocityPIN = velocityPIN;
        enginePositivePIN = positivePIN;
        engineNegativePIN = negativePIN;
    }

    ~Engine()
    {
        /*delete engineVelocityPIN;
        delete enginePositivePIN;
        delete engineNegativePIN;

        delete velocity;
        delete direction;*/
    }

    void setVelocity(int newVelocity)
    {
        analogWrite(engineVelocityPIN, newVelocity);
    }

    void intitateEngine()
    {
        pinMode(engineVelocityPIN, OUTPUT);
        pinMode(enginePositivePIN, OUTPUT);
        pinMode(engineNegativePIN, OUTPUT);
        digitalWrite(enginePositivePIN, LOW);
        digitalWrite(engineNegativePIN, HIGH);
    }
    void directionReverse()
    {
        // May change depending on connection to enginedriver hardware
        // IDEA: add if- depending on bool diretion.

        digitalWrite(enginePositivePIN, LOW);
        digitalWrite(engineNegativePIN, HIGH);
    }
};

//---------Servo class---------------

class Servo
{
private:
    // TODO: Add PINs
    int direction{};

public:
    Servo()
    {
    }

    ~Servo()
    {
        // delete direction;
    }

    void setDirection(int newDirection)
    {
        // IDEA: Decide velocity by moving the pointer in tiny steps with delay??
    }
};
