/*
 * USsensor.cpp
 */

#include <Arduino.h>
#include "Sensors/usSensor.h"

/**
 * @brief Constructs a USsensor object.
 *
 * @param triggerPIN The pin number for triggering the sensor.
 * @param receiverPIN The pin number for receiving the sensor's echo.
 */
USsensor::USsensor(int triggerPIN, int recieverPIN)
{
    sensorTriggerPIN = triggerPIN;
    sensorRecieverPIN = recieverPIN;
}

/**
 * @brief Initializes the ultrasonic sensor.
 *
 */
void USsensor::initiateUSsensor()
{
    pinMode(sensorTriggerPIN, OUTPUT);
    pinMode(sensorRecieverPIN, INPUT);
}

/**
 * @brief Gets the most current sensor reading.
 *
 * @return The most recent distance reading in centimeters.
 */
long USsensor::getDistance()
{
    return distance;
}

/**
 * @brief Performs a new reading of the sensor and updates the distance.
 *
 * This function triggers the sensor, waits for the echo, and updates the
 * distance member with the new reading.
 */
void USsensor::readDistance()
{
    digitalWrite(sensorTriggerPIN, LOW);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    digitalWrite(sensorTriggerPIN, HIGH);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    digitalWrite(sensorTriggerPIN, LOW);

    pinMode(sensorRecieverPIN, INPUT);

    long messurement = pulseIn(sensorRecieverPIN, HIGH);

    distance = (messurement / 2) / 29.1; // Convert distance from inch to cm
}