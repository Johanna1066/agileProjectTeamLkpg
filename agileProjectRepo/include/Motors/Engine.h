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
    int engineVelocityPIN{};
    int enginePositivePIN{};
    int engineNegativePIN{};

    int currentVelocity{};
    bool direction{true}; // true = forward, false = backwards

public:
    /**
     * @brief Constructs an Engine object.
     *
     * @param velocityPIN The pin number for controlling velocity.
     * @param positivePIN The pin number for forward direction.
     * @param negativePIN The pin number for backward direction.
     */
    Engine(int velocityPIN, int positivePIN, int negativePIN);

    ~Engine();

    /**
     * @brief Sets the velocity of the engine.
     *
     * @param newVelocity The new velocity to set, rescaled using the Arduino
     * map function to the desired range for the engine.
     * @param obstacle Indicates if there is an obstacle in the way (true if obstacle present,
     * false otherwise). If true, the engine should hinder forward movement.
     */
    void setVelocity(int, bool);

    /**
     * @brief Reverses the direction of the engine.
     */
    void directionReverse();

    /**
     * @brief Initializes the engine.
     */
    void intitateEngine();
};