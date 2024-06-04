#include "ESP32Servo.h"

/*
 * The SteeringServo class is responsible for controlling the servos
 * that controll the steering of the car.
 * The class mostly utilises the funtions of the "ESP32Servo.h" library
 * with the creation of the servoObject object in each SteeringServo object.
 *
 * The member ServoPIN(int) is the hardware connection and need to be given
 * when an SteeringServo object is created.
 *
 * direction(int) helps to make sure that the direction is only set if the
 * direction har actually changed since the last call.
 */
class SteeringServo
{
private:
    int servoPIN{};

    int direction{60};

    Servo servoObject;

public:
    SteeringServo(int engineServoPIN);

    ~SteeringServo();

    /*does all of the necessary electronic setup for the hardware
    to work properly.*/
    void initiateServo();

    /*takes one argument inDirection(int) that is rescaled using the arduino
    map-funtion to the desired new direction for the engine.*/
    void setDirection(int newDirection);
};
