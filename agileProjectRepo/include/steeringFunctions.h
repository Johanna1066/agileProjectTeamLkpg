/*
 * Header file containing all of the function definitions and globlal variables
 * used by main.cpp to run the car.
 *
 * setEnginevelocity(int velocity, bool obsticle) -
 *            loops thorugh the vector of engine objects and sets all
 *            their velocities and/or direction accordingly to the inarguments.
 *
 *
 * OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) -
 *            function that runs when the controller esp32 sends
 *            any data to the car esp32. Depending on the data recieved it's
 *            either handled as a engine command or as a servo command.
 *
 *
 * intitate -
 *            Initiate runs at the start of setup() in main.cpp and makes sure
 *            that the hardware is initiated, the communication protocol is
 *            initiated and set up correctly and the semaphore mutex handles
 *            are created.
 *
 *
 * sensorcheck -
 *            Makes a reading of the sensor object and if there is the bool
 *            hinderForwardMovement is set to true, if it's not the bool is set
 *            to false.
 *
 */

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <vector>

#include "Sensors/USsensor.h"
#include "Motors/Engine.h"
#include "Motors/SteeringServo.h"

std::vector<Engine> engines;
Engine right(A1, D5, D6);
Engine left(A2, D3, D4);
SemaphoreHandle_t engineHandle;

SteeringServo myServo(9);
int safeServoDistance{20};
SemaphoreHandle_t servoHandle;

USsensor mySensor(D8, D7); // TODO: Change to correct PINs
bool hinderForwardMovement = false;

int reading{};
int dataRecieved{};

// Goes thorugh the vector of engine objects and adjusts their direction and/or velocity
void setEnginesVelocity(int, bool);

// Handles recieved data and sends it to either engines or servo
void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

void initate();

void setEnginesVelocity(int velocity, bool obsticle)
{
    for (auto &engine : engines)
    {
        engine.setVelocity(velocity, obsticle);
    }
}

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
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

void initiate()
{
    myServo.initiateServo();
    for (auto &engine : engines)
    {
        engine.intitateEngine();
    }
    mySensor.initiateUSsensor();

    engineHandle = xSemaphoreCreateMutex();
    servoHandle = xSemaphoreCreateMutex();
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
    esp_now_register_recv_cb(onDataRecv);
}

void sensorCheck(void *parameters)
{
    for (;;)
    {
        mySensor.USsensor::readDistance();
        reading = mySensor.USsensor::getDistance();

        if (reading < safeServoDistance)
        {
            if (xSemaphoreTake(engineHandle, portMAX_DELAY) == pdTRUE)
            {
                if (!hinderForwardMovement)
                {
                    hinderForwardMovement = true;
                }
                xSemaphoreGive(engineHandle);
            }
        }
        else
        {
            if (xSemaphoreTake(engineHandle, portMAX_DELAY) == pdTRUE)
            {
                if (hinderForwardMovement)
                {
                    hinderForwardMovement = false;
                }
                xSemaphoreGive(engineHandle);
            }
        }
        vTaskDelay(10);
    }
}