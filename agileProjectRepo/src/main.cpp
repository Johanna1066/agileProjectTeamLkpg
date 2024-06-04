/*
https://github.com/Johanna1066/agileProjectTeamLkpg/
Controller arduino code for a 'Arduino nano ESP32'
Using object oriented code. Joystick objects get assigned a PIN that can read the joystick directions
Using tasks to allow signal inputs from both joysticks
Sending code to another 'Arduino nano ESP32' over WiFi using the recivers MAC adress

Using the esp_now protocol to connect to another 'Arduino nano ESP32' without having to connect to a network
*/
#include <Arduino.h>
#include "Sensors/Joystick.h"
#include <esp_now.h>
#include <WiFi.h>
#include "semphr.h"
#include "Namespace.h"


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

      controllerNames::reading += 10000;  //This reading is larger so we on the reciver side can
                                          // easily see which task is sending us a reading value

      esp_err_t result = esp_now_send(controllerNames::broadcastAddress, (uint8_t *)&controllerNames::reading, sizeof(controllerNames::reading));

      xSemaphoreGive(controllerNames::myHandle);
    }
    vTaskDelay(5);
  }
}