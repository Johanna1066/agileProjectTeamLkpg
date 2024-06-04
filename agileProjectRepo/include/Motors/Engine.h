/*
 *
 *
 *
 * The Engine class is responsible for controlling the speed of the engines.
 * The members engineVelocityPIN, enginePositivePIN, and engineNegativePIN are
 * the hardware connection and need to be given when an engine object is created.
 *
 * direction(bool) keeps track if the engine is currently going backwards or
 * forward. currentVelocity(int) helps to make sure that the velocity is only
 * set if the velocity has actually changed since the last call.
 *
 * The class has three methods:
 *       setVelocity - takes two arguments, inVelocity(int) that is rescaled
 *                     using  the arduino map-funtion to the desired new
 *                     velocity for the engine. The other is obsticle(bool)
 *                     that should be true of there is an obsticle in the way
 *                     and the engine should hinder movement forwards.
 *  directionReverse - does the electronic switch between forward and backwards
 *                      movement.
 *    intitateEngine - does all of the necessary electronic setup for the
 *                     hardware to work properly.
 *
 */

class Engine
{
private:
    int engineVelocityPIN{};
    int enginePositivePIN{};
    int engineNegativePIN{};

    int currentVelocity{};
    bool direction{true}; // true = forward, false = backwards

public:
    Engine(int velocityPIN, int positivePIN, int negativePIN);
    ~Engine();
    void setVelocity(int, bool);
    void intitateEngine();
    void directionReverse();
};

Engine::Engine(int velocityPIN, int positivePIN, int negativePIN)
{
    engineVelocityPIN = velocityPIN;
    enginePositivePIN = positivePIN;
    engineNegativePIN = negativePIN;
}

Engine::~Engine()
{
}

void Engine::directionReverse()
{
    if (direction)
    {
        digitalWrite(enginePositivePIN, LOW);
        digitalWrite(engineNegativePIN, HIGH);
    }
    else
    {
        digitalWrite(enginePositivePIN, HIGH);
        digitalWrite(engineNegativePIN, LOW);
    }
}

void Engine::setVelocity(int inVelocity, bool obsticle)
{
    int newVelocity = map(inVelocity, 0, 4096, -255, 255);

    if (newVelocity == currentVelocity)
    {
        return;
    }
    else
    {
        currentVelocity = newVelocity;
    }

    if ((newVelocity > -50) && (newVelocity < 20)) // Because of the hardware used there is a need for stabilizing
    {                                              // of the numbers recieved from the method call
        newVelocity = 0;
    }

    if (obsticle && (newVelocity > 0))
    {
        newVelocity = 0;
    }

    if (newVelocity < 0)
    {
        if (direction)
        {
            directionReverse();
            direction = false;
        }
    }
    else if (newVelocity > 0)
    {
        if (!direction)
        {
            directionReverse();
            direction = true;
        }
    }
    analogWrite(engineVelocityPIN, abs(newVelocity));
}

void Engine::intitateEngine()
{
    pinMode(engineVelocityPIN, OUTPUT);
    pinMode(enginePositivePIN, OUTPUT);
    pinMode(engineNegativePIN, OUTPUT);
    digitalWrite(enginePositivePIN, HIGH);
    digitalWrite(engineNegativePIN, LOW);
}