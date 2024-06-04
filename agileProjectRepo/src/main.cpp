/*
 * main.cpp
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
