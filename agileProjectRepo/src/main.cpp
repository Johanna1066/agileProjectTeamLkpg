#include <Arduino.h>
#include <iostream>

#include "motorClass.h"
// #include "sensorClass.h"
// #include "observerClass.h"

Engine right(A1, D6, D5);
engineServo carStearing(A2, 90);  //just tmp code

void setup()
{
  right.intitateEngine();
}

void loop()
{
  carStearing.setDirection(115);
  right.setVelocity(255);
  delay(5000);
  carStearing.setDirection(75);
  right.setVelocity(0);
  delay(5000);
}
