#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <vector>
#include "ESP32Servo.h"

#include "Sensors/USsensor.h"
#include "Motors/Engine.h"
#include "Motors/SteeringServo.h"
#include "steeringFunctions.h"

#include "semphr.h"

// Car code

// Handle för att styra engine
SemaphoreHandle_t engineHandle;
SemaphoreHandle_t servoHandle;

void sensorCheck(void *parameters);

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&dataRecieved, incomingData, sizeof(dataRecieved));

    if (dataRecieved >= 10000)
    {
        if (xSemaphoreTake(servoHandle, portMAX_DELAY) == pdTRUE)
        {
            dataRecieved -= 10000;

            myServo.setDirection(dataRecieved);
            delay(1);
            xSemaphoreGive(servoHandle);
        }
    }
    else if ((dataRecieved >= 0) && (dataRecieved <= 4096))
    {
        if (xSemaphoreTake(engineHandle, portMAX_DELAY) == pdTRUE)
        {

            setEnginesVelocity(dataRecieved, hinderForwardMovement);
            delay(1);
            xSemaphoreGive(engineHandle);
        }
    }
}

void setup()
{

    Serial.begin(115200);

    engineHandle = xSemaphoreCreateMutex();
    servoHandle = xSemaphoreCreateMutex();

    initiate();

    if (xTaskCreate(sensorCheck, "*sensorCheck", 4096, NULL, 1, NULL) != pdPASS)
    {
        Serial.println("Error creating task");
        return;
    }

    if (engineHandle == NULL)
    {
        Serial.println("Error creating engine semaphore");
        return;
    }
    if (servoHandle == NULL)
    {
        Serial.println("Error creating servo semaphore");
        return;
    }

    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info
    esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
}

void sensorCheck(void *parameters)
{
    for (;;)
    {
        mySensor.readDistance();
        reading = mySensor.getDistance();

        if (reading < 20)
        {
            if (xSemaphoreTake(engineHandle, portMAX_DELAY) == pdTRUE)
            {
                hinderForwardMovement = true;
                xSemaphoreGive(engineHandle);
            }
        }
        else
        {
            if (xSemaphoreTake(engineHandle, portMAX_DELAY) == pdTRUE)
            {

                hinderForwardMovement = false;
                xSemaphoreGive(engineHandle);
            }
        }

        vTaskDelay(10);
    }
}