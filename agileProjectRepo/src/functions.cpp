#include "functions.h"
#include <Arduino.h>
#include "Sensors/joystick.h"
#include <esp_now.h>
#include <WiFi.h>
#include "semphr.h"
#include "controllerNamespace.h"

/**
 * @brief Task function to read and send vertical joystick data.
 * 
 * @param parameter Pointer to task parameters (not used).
 */
void verticalReadSend(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(controllerNames::joystickHandle, portMAX_DELAY) == pdTRUE)
    {
      controllerNames::verticalJoystick.doReading();
      controllerNames::reading = controllerNames::verticalJoystick.getValue();

      esp_err_t result = esp_now_send(controllerNames::broadcastAddress, (uint8_t *)&controllerNames::reading, sizeof(controllerNames::reading));

      xSemaphoreGive(controllerNames::joystickHandle);
    }
    vTaskDelay(5);
  }
}

/**
 * @brief Task function to read and send horizontal joystick data.
 * 
 * @param parameter Pointer to task parameters (not used).
 */
void horizontalReadSend(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(controllerNames::joystickHandle, portMAX_DELAY) == pdTRUE)
    {
      controllerNames::horizontalJoystick.doReading();
      controllerNames::reading = controllerNames::horizontalJoystick.getValue();

      // Increment value to distinguish between vertical and horizontal readings in the receiver code
      controllerNames::reading += 10000;

      esp_err_t result = esp_now_send(controllerNames::broadcastAddress, (uint8_t *)&controllerNames::reading, sizeof(controllerNames::reading));

      xSemaphoreGive(controllerNames::joystickHandle);
    }
    vTaskDelay(5);
  }
}

/**
 * @brief Callback function for ESP-NOW data sent event.
 * 
 * @param mac_addr The MAC address of the receiver.
 * @param status The status of the sent packet (success or failure).
 */
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

/**
 * @brief Initializes the system, including serial communication, joysticks, semaphore, WiFi, and ESP-NOW.
 */
void initiate()
{
  Serial.begin(9600);
  controllerNames::verticalJoystick.initiateJoystick();
  controllerNames::horizontalJoystick.initiateJoystick();
  controllerNames::joystickHandle = xSemaphoreCreateMutex();

  if (controllerNames::joystickHandle == NULL)
  {
    Serial.println("Error creating semaphore");
    return;
  }

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(controllerNames::peerInfo.peer_addr, controllerNames::broadcastAddress, 6);
  controllerNames::peerInfo.channel = 0;
  controllerNames::peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&controllerNames::peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
}
