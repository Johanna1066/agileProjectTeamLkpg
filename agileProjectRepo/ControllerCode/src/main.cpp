/*
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

//SemaphoreHandle_t myHandle;
void horizontalReadSend(void *parameters);
void verticalReadSend(void *parameters);

//esp_now_peer_info_t peerInfo;
//uint8_t broadcastAddress[] = {0xEC, 0xDA, 0x3B, 0x60, 0xCD, 0xB4};
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

//Joystick verticalJoystick(A2);
//Joystick horizontalJoystick(A4);

void setup()
{
  Serial.begin(9600);
  nameMain::verticalJoystick.initiateJoystick();
  nameMain::horizontalJoystick.initiateJoystick();

  nameMain::myHandle = xSemaphoreCreateMutex();
  
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(nameMain::peerInfo.peer_addr, nameMain::broadcastAddress, 6);
  nameMain::peerInfo.channel = 0;
  nameMain::peerInfo.encrypt = false;

  (esp_now_add_peer(&nameMain::peerInfo) != ESP_OK);
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
    if (xSemaphoreTake(nameMain::myHandle, portMAX_DELAY) == pdTRUE)
    {
      nameMain::verticalJoystick.doReading();
      nameMain::reading = nameMain::verticalJoystick.getValue();

      esp_err_t result = esp_now_send(nameMain::broadcastAddress, (uint8_t *)&nameMain::reading, sizeof(nameMain::reading));
      xSemaphoreGive(nameMain::myHandle);
    }
    vTaskDelay(10);
  }
}

void horizontalReadSend(void *parameter)
{
  for (;;)
  {
    if (xSemaphoreTake(nameMain::myHandle, portMAX_DELAY) == pdTRUE)
    {
      nameMain::horizontalJoystick.doReading();
      nameMain::reading = nameMain::horizontalJoystick.getValue();

      nameMain::reading += 10000; //Sending a larger reading here so we easily can see which task sends which value in reciver Arduino

      esp_err_t result = esp_now_send(nameMain::broadcastAddress, (uint8_t *)&nameMain::reading, sizeof(nameMain::reading));
      xSemaphoreGive(nameMain::myHandle);
    }
    vTaskDelay(10);
  }
}