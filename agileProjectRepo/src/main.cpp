/**
 * @brief Car Arduino code for an 'Arduino Nano ESP32'.
 *
 * @details This code uses object-oriented programming to control the
 * components steering the car.
 * @link https://github.com/Johanna1066/agileProjectTeamLkpg/
 *
 * This implementation includes:
 * - SteeringServo objects assigned to pins for controlling the steering of
 *   the car.
 * - Engine objects assigned to pins for controlling the car's velocity and direction.
 * - USsensor objects assigned to pins to ensure there are no obstacles blocking the way.
 * - Tasks for reading and handling the sensor data.
 * - Using the ESP-NOW protocol to receive data from the
 *   controller Arduino Nano ESP32.
 *
 */

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <vector>

#include "steeringFunctions.h"

void setup()
{
    initiate();
    if (xTaskCreate(sensorCheck, "*sensorCheck", 4096, NULL, 1, NULL) != pdPASS)
    {
        Serial.println("Error creating task");
        return;
    }
}

void loop()
{
}
