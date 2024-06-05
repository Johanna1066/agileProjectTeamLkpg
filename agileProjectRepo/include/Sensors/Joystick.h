/*
 * @brief Joystick class
 * Each object of the Joystick class controls one joystick direction.
 *
 * The default constructor Joystick(int) requires an Arduino PIN to function.
 * This allows the Joystick to read and get values from the joystick.
 *
 * Joystick has 3 methods: initiateJoystick(), doReading(), and getValue()
 *
 * Joystick has 3 private variables: joystickAnalogPIN, currentValue, and initialCenter
 */
class Joystick
{
private:
    // @brief used in initiateJoystick. Gets its value from the constructor Joystick(int PIN)
    int joystickAnalogPIN{};
    // @brief stores the joystick's current value, updated in doReading()
    int currentValue{};
    // @brief used to find and map the center value of the joystick
    int initialCenter{};
public:
    /*
     * @brief Constructor that initializes joystickAnalogPIN with the provided pin number
     */
    Joystick(int pinIN);

    /*
     * @brief Destructor
     */
    ~Joystick();

    /*
     * @brief Used in setup to assign the analog PIN to the joystick
     */
    void initiateJoystick();

    /*
     * @brief Reads the joystick value and updates currentValue after remapping it
     */
    void doReading();

    /*
     * @brief Returns the currentValue after mapping it
     */
    int getValue();
};
