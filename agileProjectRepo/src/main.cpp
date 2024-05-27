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




/*
void readSensor(void *parameters)
{
  for (;;)
  {
    mySensor.taskReadDistance();

      if (mySensor.getDistance() < 20) //make function
      {
        stopEngines();
        Serial.println("STOP!");
        hinderForwardMovement = true;
        //add connect to enginevelocity
      }
      else 
      {
        hinderForwardMovement = false;
      }                               //--------------
    
    vTaskDelay(100 / portTICK_PERIOD_MS);
    
    //Send radio Signal here
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
}*/





void setup()
{
  initiate();
  Serial.begin(9600);
  myServo.initiateServo();
  /*
  xTaskCreate(
      readSensor,    // Function name
      "*readSensor", // Task name
      1000,          // Stack size
      NULL,          // Task parameters
      1,             // Task priority
      NULL           // Task handle
      
  );
  */
/*
  xTaskCreate(
      printSensorReading,    // Function name
      "*printSensorReading", // Task name
      1000,                  // Stack size
      NULL,                  // Task parameters
      1,                     // Task priority
      NULL                   // Task handle
  );*/
}

void loop()
{
horizontalJoystick.horizontalRead();
reading = horizontalJoystick.getHorizontalValue();
reading = (reading / 34);
Serial.printf("horizontalValue = %d \n", reading);
myServo.setDirection(reading);

verticalJoystick.vertialRead();
reading = verticalJoystick.getVerticalValue();
reading = ((reading / 8) - 255);
Serial.printf("verticalValue = %d \n", reading);

Serial.println("-------------------------------");
}
