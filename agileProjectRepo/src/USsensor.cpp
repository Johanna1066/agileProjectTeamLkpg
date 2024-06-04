#include <Arduino.h>
#include "Sensors/USsensor.h"

USsensor::USsensor(int triggerPIN, int recieverPIN)
{
    sensorTriggerPIN = triggerPIN;
    sensorRecieverPIN = recieverPIN;
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