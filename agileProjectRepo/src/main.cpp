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

long reading1{};

void functionCaller(void *parameters)
{

  mySensor.readDistance();
  vTaskDelay(100 / portTICK_PERIOD_MS);

}

void setup()
{
  Serial.begin(9600);
  mySensor.initiateUSsensor();

  xTaskCreate(
      functionCaller,      // Function name
      "*taskReadDistance", // Task name
      1000,                // Stack size
      NULL,                // Task parameters
      1,                   // Task priority
      NULL                 // Task handle
  );
}


void loop()
{
  reading1 = mySensor.getDistance();
  Serial.println(reading1);
}
