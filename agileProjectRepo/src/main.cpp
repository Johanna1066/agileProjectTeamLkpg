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
  delay(5000);

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
  Serial.println("Setup complete");
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
      // Read vertical joystick value
      controllerNames::verticalJoystick.doReading();
      controllerNames::reading = controllerNames::verticalJoystick.getValue();
      // Send reading

      // TODO: add differentiation between what this and the next task sends
      esp_err_t result = esp_now_send(controllerNames::broadcastAddress, (uint8_t *)&controllerNames::reading, sizeof(controllerNames::reading));
      if (result == ESP_OK)
      {
        // Serial.println("Sent with success");
      }
      else
      {
        // Serial.println("Error sending the data");
      }
      Serial.print("vertical: ");
      Serial.println(controllerNames::reading);
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
      // Read vertical joystick value
      controllerNames::horizontalJoystick.doReading();
      controllerNames::reading = controllerNames::horizontalJoystick.getValue();

      controllerNames::reading += 10000;

      // Send reading
      esp_err_t result = esp_now_send(controllerNames::broadcastAddress, (uint8_t *)&controllerNames::reading, sizeof(controllerNames::reading));
      if (result == ESP_OK)
      {
        // Serial.println("Sent with success");
      }
      else
      {
        // Serial.println("Error sending the data");
      }
      Serial.print("horizontal: ");
      Serial.println(controllerNames::reading);
      xSemaphoreGive(controllerNames::myHandle);
    }
    vTaskDelay(5);
  }
}