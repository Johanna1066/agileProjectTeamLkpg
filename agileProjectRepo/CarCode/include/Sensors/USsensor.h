#pragma once
/*
The sensor class is responsible for controlling the ultra sonic sensors
 of the car. The members sensorTriggerPIN and sensorRecieverPIN are the 
 hardware connection and need to be given when a sensor object is created.

distance(int) keeps track of the value of the latest reading of the sensor
 and is a distance in cm.

 The class has three methods; initiateSensor - does all of the necessary electronic setup for the
                                               hardware to work properly.
                              getDistance - returns the most current sensor reading.
                              readDistance - does a new reading of the sensor and updates distance.

*/

class USsensor
{
private:
    int sensorTriggerPIN;
    int sensorRecieverPIN;

    long distance{};

public:
    USsensor(int triggerPIN, int recieverPIN);
    ~USsensor();
    void initiateUSsensor();
    long getDistance();
    void readDistance();
};

USsensor::USsensor(int triggerPIN, int recieverPIN)
{
    sensorTriggerPIN = triggerPIN;
    sensorRecieverPIN = recieverPIN;
}

USsensor::~USsensor()
{
}

void USsensor::initiateUSsensor()
{
    pinMode(sensorTriggerPIN, OUTPUT);
    pinMode(sensorRecieverPIN, INPUT);
}

long USsensor::getDistance()
{
    return distance;
}

void USsensor::readDistance()
{
    digitalWrite(sensorTriggerPIN, LOW);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    digitalWrite(sensorTriggerPIN, HIGH);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    digitalWrite(sensorTriggerPIN, LOW);

    pinMode(sensorRecieverPIN, INPUT);

    long messurement = pulseIn(sensorRecieverPIN, HIGH);

    distance = (messurement / 2) / 29.1; // Convert distance to cm
}