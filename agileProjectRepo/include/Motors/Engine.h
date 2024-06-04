/*
 * The Engine class is responsible for controlling the speed of the engines.
 * The members engineVelocityPIN(int), enginePositivePIN(int), '
 * and engineNegativePIN(int) are the hardware connection and need to be
 * given when an engine object is created.
 *
 * direction(bool) determines if the engine is currently going backwards or
 * forward, true = forward and false = backwards.
 *
 * currentVelocity(int) helps to make sure that the velocity is only set if
 * the velocity has actually changed since the last call.
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

    /*takes two arguments, inVelocity(int) that is rescaledusing the arduino
    map-funtion to the desired new velocity for the engine. The other is
    obsticle(bool) that should be true of there is an obsticle in the way
    and the engine should hinder movement forwards.*/
    void setVelocity(int, bool);

    // does the electronic switch between forward and backwards movement.
    void directionReverse();

    // does all of the necessary electronic setup for the hardware to work properly.
    void intitateEngine();
};
