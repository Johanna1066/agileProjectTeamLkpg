#include <Arduino.h>
#include <iostream>
#include <vector>


#include "motorClass.h"
#include "sensorClass.h"
#include "observerClass.h"

USsensor testSensor(D2, D3);
//AntiCrashAhead testCrash(20);
std::vector <AntiCrash> testCrashObjects;
AntiCrash* tmp;




void setup()
{
    Serial.begin(9600);
    testSensor.USsensorInitiate();
    for(int i = 0; i < 10; i++)
{
    tmp = new AntiCrash(20);
    testCrashObjects.push_back(*tmp);
}
}

void loop()
{
    testSensor.readDistance();
    
}
