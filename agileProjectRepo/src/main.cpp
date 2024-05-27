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
}

void horizontalJoystickRead(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE)
    { // Use portMAX_DELAY to block indefinitely
      horizontalJoystick.horizontalRead();
      reading = horizontalJoystick.getHorizontalValue();
      reading = (reading / 34);

      if ((reading > 55) && (reading < 60))
      {
        reading = 58;
      }
      Serial.printf("horizontalValue = %d \n", reading);
      myServo.setDirection(reading);
      xSemaphoreGive(myHandle);
    }

    //vTaskDelay(1);
  }
}

void verticalJoystickRead(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE)
    {
      verticalJoystick.vertialRead();
      reading = verticalJoystick.getVerticalValue();
      reading = ((reading / 8) - 255);
      // Serial.printf("verticalValue = %d \n", reading);
      xSemaphoreGive(myHandle);
    }
    //vTaskDelay(1);
  }
}
