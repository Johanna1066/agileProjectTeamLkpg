#include <Arduino.h>
#include <iostream>
#include <vector>

#include "semphr.h"



// xSemaphoreTake(),, xSemaphoreGive()

int counter = 0;
SemaphoreHandle_t myHandle;
void myFunctionAdd(void *parameters);
void myFunctionPrint(void *parameters);


void setup()
{
    myHandle = xSemaphoreCreateMutex();

    Serial.begin(9600);
  xTaskCreate(
    myFunctionAdd,
    "*myFunctionAdd",
    2048,
    NULL,
    1,
    NULL
    );

     xTaskCreate(
    myFunctionPrint,
    "*myFunctionPrint",
    2048,
    NULL,
    1,
    NULL
    );
}

void myFunctionAdd(void *parameter){
   for (;;)
   {
    if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE) {  // Use portMAX_DELAY to block indefinitely
            counter++;
            xSemaphoreGive(myHandle);
        }
    
    vTaskDelay(100);
   }
}

void myFunctionPrint(void *parameter){
    for (;;)
    {
        if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE) {
            Serial.println(counter);
            xSemaphoreGive(myHandle);
        }
        vTaskDelay(1000);
    }

}

void loop()
{


  
}
