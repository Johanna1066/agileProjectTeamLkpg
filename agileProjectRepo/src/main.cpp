#include <Arduino.h>
#include <iostream>
#include <vector>
#include "sensorClass.h"

int count1 = 0;
int count2 = 0;

joystick testJoystick(A3, A4, 5);

void task1(void * parameters){
  for(;;){
    testJoystick.horizontalRead();
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

void task2(void * parameters){
  for(;;){
    testJoystick.vertialRead();
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

void taskPrint( void * parameters){
  for(;;){
    count1 = testJoystick.getHorizontalValue();
    //count2 = testJoystick.getVerticalValue();
    Serial.println(count1);
    //Serial.println(count2);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}



void setup(){
  Serial.begin(9600);
  testJoystick.joystickInitiate();

  xTaskCreate(task1, "*Task 1", 1000, NULL, 1, NULL);
/*
   xTaskCreate(
    task2,    //Function name
    "*Task 2", //Task name
    1000,     //Stack size
    NULL,     //Task parameters
    1,        //Task priority
    NULL      //Task handle
  );
  */

  xTaskCreate(
    taskPrint,    //Function name
    "*Task Print", //Task name
    1000,     //Stack size
    NULL,     //Task parameters
    1,        //Task priority
    NULL      //Task handle
  );

  
}

void loop()
{

}
