#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <vector>
#include "ESP32Servo.h"

#include "Sensors/USsensor.h"
#include "Motors/Engine.h"
#include "Motors/SteeringServo.h"
#include "steeringFunctions.h"

#include "semphr.h"

// Car code

// Handle för att styra engine
SemaphoreHandle_t engineHandle;
SemaphoreHandle_t servoHandle;

void sensorCheck(void *parameters);
void printOut(int);

// Comunication code

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&dataRecieved, incomingData, sizeof(dataRecieved));
  
  if (dataRecieved >= 10000)
  {
    if (xSemaphoreTake(servoHandle, portMAX_DELAY) == pdTRUE)
    {
      dataRecieved -= 10000;
     
      myServo.setDirection(dataRecieved);
      // Serial.print("Servodata: ");
      // Serial.println(dataRecieved);
      xSemaphoreGive(servoHandle);
    }
  }
  else if ((dataRecieved >= 0) && (dataRecieved <= 4096))
  {
    if (xSemaphoreTake(engineHandle, portMAX_DELAY) == pdTRUE)
    {


      setEnginesVelocity(dataRecieved, hinderForwardMovement);
      // Serial.print("Enginedata: ");
      // Serial.println(dataRecieved);
      xSemaphoreGive(engineHandle);
    }
  }
}

void setup()
{
  // Init Serial Monitor
  Serial.begin(115200);
  // Create semaphore
  engineHandle = xSemaphoreCreateMutex();
  servoHandle = xSemaphoreCreateMutex();

  initiate();

  if (engineHandle == NULL)
  {
    Serial.println("Error creating engine semaphore");
    return;
  }
  if (servoHandle == NULL)
  {
    Serial.println("Error creating servo semaphore");
    return;
  }

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  // Create tasks

  if (xTaskCreate(
          sensorCheck,
          "*sensorCheck",
          4096,
          NULL,
          1,
          NULL) != pdPASS)
  {
    Serial.println("Error creating task");
    return;
  }
}

void loop()
{
}

void sensorCheck(void *parameters)
{
  for (;;)
  {
    mySensor.readDistance();
    reading = mySensor.getDistance();

    reading = 200; //Temporary removal ov antikrash

    if (reading < 20)
    {
      if (xSemaphoreTake(engineHandle, portMAX_DELAY) == pdTRUE)
      {
        hinderForwardMovement = true;
        xSemaphoreGive(engineHandle);
      }
    }
    else
    {
      if (xSemaphoreTake(engineHandle, portMAX_DELAY) == pdTRUE)
      {

        hinderForwardMovement = false;
        xSemaphoreGive(engineHandle);
      }
    }

    vTaskDelay(10);
  }
}
