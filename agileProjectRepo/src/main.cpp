#include <Arduino.h>
#include <iostream>

#include "motorClass.h"
#include "sensorClass.h"
#include "observerClass.h"

USsensor testSensor(D2, D3);

void setup()
{
    Serial.begin(9600);
    testSensor.USsensorInitiate();
}

void loop()
{
    testSensor.readDistance();
}
