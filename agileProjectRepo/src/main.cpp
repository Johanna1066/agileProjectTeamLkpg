#include <Arduino.h>
#include <iostream>
#include <vector>

#include "Motors/Engine.h"
#include "Motors/SteeringServo.h"
#include "Sensors/Joystick.h"
#include "Sensors/USsensor.h"
#include "steeringFunctions.h"

void stopEngines();
void setEnginesVelocity(int);
void initate();

void setup()
{
  initiate();
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
