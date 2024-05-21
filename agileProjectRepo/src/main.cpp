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

void readSensor(void *parameters)
{
  for (;;)
  {
    mySensor.taskReadDistance();
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void printSensorReading(void *parameters)
{
  for (;;)
  {
    reading = mySensor.getDistance();
    Serial.println(reading);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup()
{
  Serial.begin(9600);
  mySensor.initiateUSsensor();

  xTaskCreate(
      readSensor,    // Function name
      "*readSensor", // Task name
      2000,          // Stack size
      NULL,          // Task parameters
      1,             // Task priority
      NULL           // Task handle
  );

  xTaskCreate(
      printSensorReading,    // Function name
      "*printSensorReading", // Task name
      2000,                  // Stack size
      NULL,                  // Task parameters
      1,                     // Task priority
      NULL                   // Task handle
  );
}

void loop()
{
}
