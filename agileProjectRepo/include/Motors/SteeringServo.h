#include "ESP32Servo.h"

/**
 * The SteeringServo class is responsible for controlling the servos
 * that controll the steering of the car.
 * The class primarily utilises the funtions of the "ESP32Servo.h" library
 * through the creation of the servoObject within each SteeringServo object.
 *
 * The member variable ServoPIN(int) represents the hardware connection and
 * needs to be given when an SteeringServo object is created.
 *
 * The direction(int) variable ensures that the direction is only set if the
 * direction har actually changed since the last call.
 */
class SteeringServo
{
private:
    int servoPIN{}; // The pin connected to the servo

    int direction{60}; // Current direction, initialized to 60

    Servo servoObject; // Servo object from the ESP32Servo library

public:
    /**
     * @brief Constructs a SteeringServo object.
     * 
     * @param engineServoPIN The pin number where the servo is connected.
     */
    SteeringServo(int engineServoPIN);

    /**
     * @brief Destructor for the SteeringServo object.
     */
    ~SteeringServo();

    /**
     * @brief Initializes the servo.
     * 
     * Performs all necessary electronic setup for the hardware to work properly.
     */
    void initiateServo();

    /**
     * @brief Sets the direction of the servo.
     * 
     * @param newDirection The new direction to set, rescaled using the Arduino
     * map function to the desired range for the servo.
     */
    void setDirection(int newDirection);
};