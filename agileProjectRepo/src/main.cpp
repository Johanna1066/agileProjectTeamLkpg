#include <Arduino.h>
#include <iostream>
#include <vector>
#include <esp_now.h>
#include <WiFi.h>
#include <string>

#include "Sensors/Joystick.h"

#include "semphr.h"

// Joystick code

Joystick verticalJoystick(A6, A5, 12);   // Använder A6
Joystick horizontalJoystick(A6, A5, 12); // Använder A5

uint8_t reading{};

uint8_t broadcastAddress[] = {0xEC, 0xDA, 0x3B, 0x60, 0xCD, 0xB4};

esp_now_peer_info_t peerInfo;

SemaphoreHandle_t myHandle;

void horizontalJoystickReadSend(void *parameters);
void verticalJoystickReadSend(void *parameters);

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

int countDigit(int number)
{
  int count = 0;
  while (number != 0)
  {
    number = number / 10;
    count++;
  }
  return count;
}

void setup()
{
  // task things
  myHandle = xSemaphoreCreateMutex();

  Serial.begin(9600);
  xTaskCreate(
      verticalJoystickReadSend,
      "*verticalJoystickReadSend",
      4096,
      NULL,
      1,
      NULL);

  xTaskCreate(
      horizontalJoystickReadSend,
      "*horizontalJoystickReadSend",
      4096,
      NULL,
      1,
      NULL);

  //-----------Other setup---------------

  WiFi.mode(WIFI_STA);

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
}

void loop()
{
  // myServo.setDirection(60);
}

void horizontalJoystickReadSend(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE)
    { // Use portMAX_DELAY to block indefinitely
      horizontalJoystick.horizontalRead();
      reading = horizontalJoystick.getHorizontalValue();

      reading +=10000;

      // Send reading

      esp_err_t result = esp_now_send(
          broadcastAddress,           // MAC-adress of reciever unit
          (uint8_t *)&reading, // Message to send
          sizeof(reading)); // Size of message

      if (result != ESP_OK)
      {
        Serial.println("Error sending the data");
      }


      xSemaphoreGive(myHandle);
    }

    vTaskDelay(1);
  }
}

void verticalJoystickReadSend(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(myHandle, portMAX_DELAY) == pdTRUE)
    {
      verticalJoystick.vertialRead();
      reading = verticalJoystick.getVerticalValue();

      // Send reading
      esp_err_t result = esp_now_send(
          broadcastAddress, // MAC-adress of reciever unit
          (uint8_t *)&reading,     // Message to send
          sizeof(reading));     // Size of message

      if (result == ESP_OK)
      {
        esp_err_t result = esp_now_send(
            broadcastAddress,    // MAC-adress of reciever unit
            (uint8_t *)&reading, // Message to send
            sizeof(reading));    // Size of message
      }

      xSemaphoreGive(myHandle);
    }
    vTaskDelay(10);
  }
}
