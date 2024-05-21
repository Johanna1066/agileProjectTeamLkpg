#include <Arduino.h>
#include <iostream>
#include <vector>

#include "Engine.h"
#include "SteeringServo.h"
#include "Joystick.h"
#include "USsensor.h"
#include "sensorClass.h"
#include "steeringFunctions.h"

std::vector<Engine> engines;

Engine right(A1, D6, D5);
Engine left(A2, D4, D3);

USsensor mySensor(D9, D10);
long reading;

void stopEngines();
void setEnginesVelocity(int);

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

  if (reading < 20)
  {
    stopEngines();
  }
  else
  {
    setEnginesVelocity(255);
  }
}
