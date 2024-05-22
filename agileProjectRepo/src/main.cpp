#include <Arduino.h>
#include <iostream>
#include <vector>
#include "sensorClass.h"



joystick testJoystick(A3, A4, 5);

int lastHorizontalRead{};
int lastVerticalRead{};

/*
void taskSteering(void * parameters){
  for(;;){
    testJoystick.horizontalRead();
    testJoystick.vertialRead();

    if(testJoystick.getHorizontalValue() != lastHorizontalRead)
    {
      //Skicka data
      Serial.println("Ändra sväng");
    }
    if(testJoystick.getVerticalValue() != lastVerticalRead)
    {
      //Skicka data
      Serial.println("Ändra gas");
    }

    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
*/


void setup(){
  Serial.begin(9600);
  testJoystick.joystickInitiate();

  //xTaskCreate(taskSteering, "*Task 1", 1000, NULL, 1, NULL);
  
}

void loop()
{
  testJoystick.horizontalRead();
  lastHorizontalRead = testJoystick.getHorizontalValue();
  Serial.println(lastHorizontalRead);
  delay(500);
}
