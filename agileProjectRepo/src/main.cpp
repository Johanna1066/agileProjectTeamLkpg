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
#include "functions.h"

void setup()
{
  initiate();

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