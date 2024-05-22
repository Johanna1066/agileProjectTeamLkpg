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
void initiate(); 

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


//TaskState Testing
eTaskState hej{};
TaskHandle_t readSensorHandle;
TaskStatus_t xTaskDetails;

void sendRadioSignal(void *parameters) //Testing 
{
  for (;;)
  {
   
   
    // Task Status Test
    

    readSensorHandle = xTaskGetHandle("*readSensor");
    configASSERT(readSensorHandle);
    vTaskGetInfo(readSensorHandle, &xTaskDetails, pdTRUE, eInvalid);
    //-------------------
    hej = xTaskDetails.eCurrentState;
    Serial.println(hej);
    
  }
}

//--------------------------


void setup()
{
  initiate();
  Serial.begin(9600);

  xTaskCreate(
      readSensor,    // Function name
      "*readSensor", // Task name
      1000,          // Stack size
      NULL,          // Task parameters
      1,             // Task priority
      &readSensorHandle           // Task handle
  );

  xTaskCreate(
      printSensorReading,    // Function name
      "*printSensorReading", // Task name
      1000,                  // Stack size
      NULL,                  // Task parameters
      1,                     // Task priority
      NULL                   // Task handle
  );
}

void loop()
{
}
