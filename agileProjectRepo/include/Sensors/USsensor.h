#ifndef _WCC_USSENSOR_H
#define _WCC_USSENSOR_H

/**
 * The sensor class is responsible for controlling the ultra sonic sensors
 * of the car. The members sensorTriggerPIN and sensorRecieverPIN are the
 * hardware connection and need to be given when a sensor object is created.
 *
 * distance(int) is the value of the latest reading of the sensor
 * and is a distance in cm.
 */
class USsensor
{
private:
    int sensorTriggerPIN;
    int sensorRecieverPIN;

    long distance{};

public:
    USsensor(int triggerPIN, int recieverPIN);

    ~USsensor() = default;

    void initiateUSsensor();

    long getDistance();

    void readDistance();
};

#endif //_WCC_USSENSOR_H
