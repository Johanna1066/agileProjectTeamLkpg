/*
 * @brief Controller Arduino code for an 'Arduino Nano ESP32'.
 * @details This code uses object-oriented programming to manage joystick input and sends data to another 'Arduino Nano ESP32' via WiFi using ESP-NOW.
 * @link https://github.com/Johanna1066/agileProjectTeamLkpg/
 * 
 * This implementation includes:
 * - Joystick objects assigned to pins for reading joystick directions.
 * - Tasks for handling signals from both joysticks.
 * - Sending data to a receiver using its MAC address.
 * - Using the ESP-NOW protocol to connect without a network.
 */

#include <Arduino.h>
#include "Sensors/Joystick.h"
#include <esp_now.h>
#include <WiFi.h>
#include "semphr.h"
#include "controllerNamespace.h"

void horizontalReadSend(void *parameters);
void verticalReadSend(void *parameters);

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

void setup()
{
  Serial.begin(9600);
  controllerNames::verticalJoystick.initiateJoystick();
  controllerNames::horizontalJoystick.initiateJoystick();
  controllerNames::myHandle = xSemaphoreCreateMutex();

  if (controllerNames::myHandle == NULL)
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

  if (xTaskCreate(verticalReadSend, "verticalReadSend", 4096, NULL, 1, NULL) != pdPASS)
  {
    Serial.println("Error creating task");
    return;
  }

  if (xTaskCreate(horizontalReadSend, "horizontalReadSend", 4096, NULL, 1, NULL) != pdPASS)
  {
    Serial.println("Error creating task");
    return;
  }
}

void loop()
{
}

/*
 * @brief Callback function for ESP-NOW data sent event.
 * @param mac_addr The MAC address of the receiver.
 * @param status The status of the sent packet (success or failure).
 */
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void verticalReadSend(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(controllerNames::myHandle, portMAX_DELAY) == pdTRUE)
    {
      controllerNames::verticalJoystick.doReading();
      controllerNames::reading = controllerNames::verticalJoystick.getValue();

      esp_err_t result = esp_now_send(controllerNames::broadcastAddress, (uint8_t *)&controllerNames::reading, sizeof(controllerNames::reading));

      xSemaphoreGive(controllerNames::myHandle);
    }
    vTaskDelay(5);
  }
}

void horizontalReadSend(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(controllerNames::myHandle, portMAX_DELAY) == pdTRUE)
    {
      controllerNames::horizontalJoystick.doReading();
      controllerNames::reading = controllerNames::horizontalJoystick.getValue();

      controllerNames::reading += 10000;  // Increment value to distinguish between vertical and horizontal readings in the reciver code

      esp_err_t result = esp_now_send(controllerNames::broadcastAddress, (uint8_t *)&controllerNames::reading, sizeof(controllerNames::reading));

      xSemaphoreGive(controllerNames::myHandle);
    }
    vTaskDelay(5);
  }
}
