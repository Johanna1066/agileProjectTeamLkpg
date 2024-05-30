#include <Arduino.h>
#include "Sensors/Joystick.h"
#include <esp_now.h>
#include <WiFi.h>
#include "semphr.h"
// Joystick code

SemaphoreHandle_t myHandle;

void horizontalReadSend(void *parameters);
void verticalReadSend(void *parameters);

int reading = 0;
int taskDelay = 10;
//int tmp{};

esp_now_peer_info_t peerInfo;
uint8_t broadcastAddress[] = {0xEC, 0xDA, 0x3B, 0x60, 0xCD, 0xB4};

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
// REPLACE WITH YOUR RECEIVER MAC Address

Joystick verticalJoystick(A2);
Joystick horizontalJoystick(A4);


void setup()
{
  // Init Serial Monitor
  Serial.begin(9600);
  verticalJoystick.initiateJoystick();
  horizontalJoystick.initiateJoystick();
  // Create semaphore
  
  myHandle = xSemaphoreCreateMutex();
  if (myHandle == NULL)
  {
    Serial.println("Error creating semaphore");
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
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Transmitted packet
  esp_now_register_send_cb(OnDataSent);
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }

  // Create tasks

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
          horizontalReadSend,
          "horizontalReadSend",
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
  // Main loop does nothing, tasks handle everything
  
  /*
  verticalJoystick.doReading();
  horizontalJoystick.doReading();
  tmp = verticalJoystick.getValue();
  Serial.printf("verticalJoystick = %d \n", tmp);
  tmp = horizontalJoystick.getValue();
  Serial.printf("horizontalJoystick = %d \n", tmp);
  Serial.println("-----------------------------------");
  delay(1000);
  */
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
    if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE)
    {
      // Read vertical joystick value
      verticalJoystick.doReading();
      reading = verticalJoystick.getValue();
      // Send reading

      //TODO: add differentiation between what this and the next task sends
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
    vTaskDelay(10);
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

      reading += 10000;

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
    vTaskDelay(10);
  }
}