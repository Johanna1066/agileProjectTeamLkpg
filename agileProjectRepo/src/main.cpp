#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#include "Sensors/Joystick.h"

#include "semphr.h"

// Joystick code

SemaphoreHandle_t myHandle;

void horizontalJoystickReadSend(void *parameters);
void verticalJoystickReadSend(void *parameters);

//____________________________________________

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xEC, 0xDA, 0x3B, 0x60, 0xCD, 0xB4};

Joystick verticalJoystick(A6, A5, 12);

int reading = 0;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
  // Init Serial Monitor
  Serial.begin(115200);
  verticalJoystick.initiateJoystick();
  myHandle = xSemaphoreCreateMutex();

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

  xTaskCreate(
      verticalJoystickReadSend,
      "*verticalJoystickReadSend",
      4096,
      NULL,
      1,
      NULL);
}

void loop()
{
}

//____________________________________________

/*
void horizontalJoystickReadSend(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE)
    { // Use portMAX_DELAY to block indefinitely
      horizontalJoystick.horizontalRead();
      reading = horizontalJoystick.getHorizontalValue();

      reading += 10000;

      // Send reading

      esp_err_t result = esp_now_send(
          broadcastAddress,    // MAC-adress of reciever unit
          (uint8_t *)&reading, // Message to send
          sizeof(reading));    // Size of message

      if (result != ESP_OK)
      {
        Serial.println("Error sending the data");
      }

      xSemaphoreGive(myHandle);
    }

    vTaskDelay(1);
  }
}*/

void verticalJoystickReadSend(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE)
    {
      verticalJoystick.verticalRead();
      reading = verticalJoystick.getVerticalValue();

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
