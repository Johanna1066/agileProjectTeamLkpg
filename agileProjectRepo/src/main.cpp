#include <Arduino.h>
#include <iostream>
#include <vector>
#include "motorClass.h"
#include "sensorClass.h"
// #include "observerClass.h"


std::vector<Engine> engines;

Engine right(A1, D6, D5);
Engine left(A2, D4, D3);

void stopEngines();
void setEnginesVelocity(int);

USsensor mySensor(D9, D10);
long reading;

void setup()
{
  engines.push_back(left);
  engines.push_back(right);

  right.intitateEngine();
  left.intitateEngine();
  mySensor.USsensorInitiate();

}

void loop()
{
  
  mySensor.readDistance();
  reading = mySensor.getDistance();

  if(reading < 20)
  {
    stopEngines();
  }
  else
  {
    setEnginesVelocity(255);
  }

}

void stopEngines()
{
  for (auto &engine : engines) 
  {
    engine.setVelocity(0);
  }
}

void setEnginesVelocity(int velocity)
{
  for (auto &engine : engines) 
  {
    engine.setVelocity(velocity);
  }
}

