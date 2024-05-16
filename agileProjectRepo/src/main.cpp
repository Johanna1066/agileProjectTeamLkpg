#include <Arduino.h>
#include <iostream>

#include "motorClass.h"
#include "sensorClass.h"
// #include "observerClass.h"

Engine right(A1, D6, D5);
Engine left(A2, D4, D3);

USsensor mySensor(D9, D10);

long reading;

void setup()
{
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

    left.setVelocity(0);
    right.setVelocity(0);
  }
  else
  {
    left.setVelocity(255);
    right.setVelocity(255);
  }



}
