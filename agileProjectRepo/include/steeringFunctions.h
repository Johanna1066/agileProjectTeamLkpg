/*
 * Header file containing all of the function definitions and globlal variables
 * used by main.cpp to run the car.
 */

#include "Sensors/USsensor.h"
#include "Motors/Engine.h"
#include "Motors/SteeringServo.h"
#include "carNamespace.h"

/* Loops through the vector of engine objects and sets all
 * their velocities and/or direction accordingly to the inarguments.*/
void setEnginesVelocity(int, bool);

/* Runs when the controller esp32 sends any data to the car esp32.
 * Depending on the data recieved it's either handled as a
 * engine command or as a servo command.*/
void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

/* Runs at the start of setup() in main.cpp and makes sure that the hardware
 * is initiated, the communication protocol is initiated and set up
 * correctly and the semaphore mutex handles are created.*/
void initate();

/* Makes a reading of the sensor object and if there is the bool
 * hinderForwardMovement is set to true, if it's not the bool is set
 * to false.*/
void sensorCheck(void *parameters);

void setEnginesVelocity(int velocity, bool obsticle)
{
    for (auto &engine : okej::engines)
    {
        engine.setVelocity(velocity, obsticle);
    }
}

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&okej::dataRecieved, incomingData, sizeof(okej::dataRecieved));

    if (okej::dataRecieved >= 10000)
    {
        if (xSemaphoreTake(okej::servoHandle, portMAX_DELAY) == pdTRUE)
        {
            okej::dataRecieved -= 10000;

            okej::myServo.setDirection(okej::dataRecieved);
            delay(1);
            xSemaphoreGive(okej::servoHandle);
        }
    }
    else if ((okej::dataRecieved >= 0) && (okej::dataRecieved <= 4096))
    {
        if (xSemaphoreTake(okej::engineHandle, portMAX_DELAY) == pdTRUE)
        {

            setEnginesVelocity(okej::dataRecieved, okej::hinderForwardMovement);
            delay(1);
            xSemaphoreGive(okej::engineHandle);
        }
    }
}

void initiate()
{
    okej::myServo.initiateServo();

    okej::engines.push_back(okej::left);
    okej::engines.push_back(okej::right);

    for (auto &engine : okej::engines)
    {
        engine.intitateEngine();
    }

    okej::mySensor.initiateUSsensor();

    okej::engineHandle = xSemaphoreCreateMutex();
    okej::servoHandle = xSemaphoreCreateMutex();

    if (okej::engineHandle == NULL)
    {
        Serial.println("Error creating engine semaphore");
        return;
    }
    if (okej::servoHandle == NULL)
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
        okej::mySensor.USsensor::readDistance();
        okej::reading = okej::mySensor.USsensor::getDistance();

        if (okej::reading < okej::safeServoDistance)
        {
            if (xSemaphoreTake(okej::engineHandle, portMAX_DELAY) == pdTRUE)
            {
                if (!okej::hinderForwardMovement)
                {
                    okej::hinderForwardMovement = true;
                }
                xSemaphoreGive(okej::engineHandle);
            }
        }
        else
        {
            if (xSemaphoreTake(okej::engineHandle, portMAX_DELAY) == pdTRUE)
            {
                if (okej::hinderForwardMovement)
                {
                    okej::hinderForwardMovement = false;
                }
                xSemaphoreGive(okej::engineHandle);
            }
        }
        vTaskDelay(10);
    }
}