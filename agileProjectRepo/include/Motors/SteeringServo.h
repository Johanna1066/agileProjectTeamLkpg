#include "ESP32Servo.h"

/*
 * The SteeringServo class is responsible for controlling the servos
 * that controll the steering of the car.
 * The class mostly utilises the funtions of the "ESP32Servo.h" library
 * with the creation of the servoObject object in each SteeringServo object.
 * The member ServoPIN are the hardware connection and need to be given
 * when an engine object is created.
 *
 * direction(int) helps to make sure that the direction is only set if the
 * direction har actually changed since the last call.
 *
 * The class has two methods:
 *              initiateServo - does all of the necessary electronic setup
 *                              for the hardware to work properly.
 *               setDirection - takes one argument inDirection(int) that is
 *                              rescaled using  the arduino map-funtion to
 *                              the desired new direction for the engine.
 *
 *
 */

class SteeringServo
{
private:
    int direction{60};
    int servoPIN{};

    Servo servoObject;

public:
    SteeringServo(int engineServoPIN);

    ~SteeringServo();

    void initiateServo();

    void setDirection(int newDirection);
};
