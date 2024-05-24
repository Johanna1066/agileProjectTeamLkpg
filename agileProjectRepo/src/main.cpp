#include <Arduino.h>
#include <iostream>
#include <ESP32Servo.h>

#include "motorClass.h"

//orange cabel is pin cable, digital
engineServo carStearing(9);

void setup()
{
  carStearing.ServoInitiate();
}

void loop()
{
  carStearing.setDirection(0);

  delay(5000);
  carStearing.setDirection(120);

  delay(5000);
}
