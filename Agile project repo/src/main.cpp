#include <Arduino.h>
#include <iostream>

#include "controllerClass.h"
#include "sensorClass.h"
#include "observerClass.h"

// put function declarations here:
int myFunction(int, int);

void setup()
{
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop()
{
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}