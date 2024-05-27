#include <Arduino.h>
#include <iostream>
#include <vector>

#include "Motors/Engine.h"
#include "Motors/SteeringServo.h"
#include "Sensors/Joystick.h"
#include "Sensors/USsensor.h"
#include "steeringFunctions.h"

#include "semphr.h"

void stopEngines();
void setEnginesVelocity(int);
void initiate();

int counter = 0;

SemaphoreHandle_t myHandle;

void horizontalJoystickRead(void *parameters);
void verticalJoystickRead(void *parameters);

void setup()
{
  myHandle = xSemaphoreCreateMutex();

  initiate();

  Serial.begin(9600);
  xTaskCreate(
      verticalJoystickRead,
      "*verticalJoystickRead",
      4096,
      NULL,
      1,
      NULL);

  xTaskCreate(
      horizontalJoystickRead,
      "*horizontalJoystickRead",
      4096,
      NULL,
      1,
      NULL);
}

void loop()
{
  // myServo.setDirection(60);
}

void horizontalJoystickRead(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE)
    { // Use portMAX_DELAY to block indefinitely
      horizontalJoystick.horizontalRead();
      reading = horizontalJoystick.getHorizontalValue();
      int test = map(reading, 0, 4095, 0, 120);

      if ((test > 50) && (test < 65))
      {
        test = 60;
      }

      myServo.setDirection(test);

      xSemaphoreGive(myHandle);
    }

    vTaskDelay(1);
  }
}

void verticalJoystickRead(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE)
    {
      horizontalJoystick.vertialRead();
      reading = horizontalJoystick.getVerticalValue();

      setEnginesVelocity(reading);
      xSemaphoreGive(myHandle);
    }
    vTaskDelay(10);
  }
}
