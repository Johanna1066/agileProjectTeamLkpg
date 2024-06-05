#ifndef _WCC_STEERINGSERVO_H
#define _WCC_STEERINGSERVO_H

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
    // The pin connected to the servo
    int servoPIN{}; 

    // Current direction, initialized to 60
    int direction{60}; 

    // Servo object from the ESP32Servo library
    Servo servoObject; 

public:
    SteeringServo(int engineServoPIN);

    ~SteeringServo() = default;

    void initiateServo();

    void setDirection(int newDirection);
};

#endif //_WCC_STEERINGSERVO_H