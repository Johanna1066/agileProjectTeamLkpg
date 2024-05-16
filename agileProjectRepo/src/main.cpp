#include <Arduino.h>
#include <iostream>

#include "motorClass.h"
// #include "sensorClass.h"
// #include "observerClass.h"

Engine right(A1, D6, D5);
Engine left(A2, D4, D3);

void setup()
{
  right.intitateEngine();
  left.intitateEngine();
}

void loop()
{
  right.setVelocity(255);
  left.setVelocity(255);
  delay(5000);
  right.setVelocity(0);
  left.setVelocity(0);
  delay(5000);
}
