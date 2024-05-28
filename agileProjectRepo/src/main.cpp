#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <vector>


#include "Sensors/USsensor.h"
#include "Motors/Engine.h"
#include "Motors/SteeringServo.h"
#include "steeringFunctions.h"


#include "semphr.h"
// Car code

SemaphoreHandle_t myHandle;



// REPLACE WITH YOUR RECEIVER MAC Address




void setup()
{
  // Init Serial Monitor
  Serial.begin(115200);
  // Create semaphore
  myHandle = xSemaphoreCreateMutex();
  if (myHandle == NULL)
  {
    Serial.println("Error creating semaphore");
    return;
  }


  // Create tasks
/*
  if (xTaskCreate(
          verticalReadSend,
          "verticalReadSend",
          4096,
          NULL,
          1,
          NULL) != pdPASS)
  {
    Serial.println("Error creating task");
    return;
  }

  if (xTaskCreate(
          verticalReadSend,
          "verticalReadSend",
          4096,
          NULL,
          1,
          NULL) != pdPASS)
  {
    Serial.println("Error creating task");
    return;
  }
  */
}

void loop()
{

}



/*
void verticalReadSend(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE)
    {
      // Read vertical joystick value
      verticalJoystick.doReading();
      reading = verticalJoystick.getValue();
      // Send reading


      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&reading, sizeof(reading));
      if (result == ESP_OK)
      {
        Serial.println("Sent with success");
      }
      else
      {
        Serial.println("Error sending the data");
      }
      xSemaphoreGive(myHandle);
    }
    vTaskDelay(100);
  }
}

void horizontalReadSend(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE)
    {
      // Read vertical joystick value
      horizontalJoystick.doReading();
      reading = horizontalJoystick.getValue();
      // Send reading
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&reading, sizeof(reading));
      if (result == ESP_OK)
      {
        Serial.println("Sent with success");
      }
      else
      {
        Serial.println("Error sending the data");
      }
      xSemaphoreGive(myHandle);
    }
    vTaskDelay(100);
  }
}

*/