#ifndef _WCC_ENGINE_H
#define _WCC_ENGINE_H

/*
 * The Engine class is responsible for controlling the speed of the engines.
 * The members engineVelocityPIN(int), enginePositivePIN(int), and
 * engineNegativePIN(int) represent the hardware connections and need to be
 * provided when an Engine object is created.
 *
 * The direction(bool) member determines if the engine is currently going
 * forwards (true) or backwards (false).
 *
 * The currentVelocity(int) member ensures that the velocity is only set if
 * it has actually changed since the last call.
 */
class Engine
{
private:
    // Pin for controlling velocity
    int engineVelocityPIN;

    // Pin for forward direction
    int enginePositivePIN;

    // Pin for backward direction
    int engineNegativePIN;

    // Current velocity of the engine
    int currentVelocity;

    // true = forward, false = backwards
    bool direction;

public:
    Engine(int velocityPIN, int positivePIN, int negativePIN);

    ~Engine() = default;

    void setVelocity(int, bool);

    void directionReverse();

    void intitateEngine();
};

#endif //_WCC_ENGINE_H