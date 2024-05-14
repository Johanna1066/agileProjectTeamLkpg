#include <Arduino.h>
#include <iostream>

#include "motorClass.h"
#include "sensorClass.h"
#include "observerClass.h"

Engine right(A1, D6, D5);

void setup()
{
  right.intitateEngine();
}

void loop()
{

  right.setVelocity(255);
  delay(5000);
  right.setVelocity(0);
  delay(5000);
}
