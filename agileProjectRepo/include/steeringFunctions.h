/**
 * Header file containing all of the function definitions and global variables
 * used by main.cpp to run the car.
 */

#include "Sensors/USsensor.h"
#include "Motors/Engine.h"
#include "Motors/SteeringServo.h"
#include "carNamespace.h"

/**
 * @brief Sets the velocity and direction of all engine objects.
 *
 * @param velocity The velocity to set for the engines.
 * @param obstacle Indicates if there is an obstacle (true if obstacle present, false otherwise).
 */
void setEnginesVelocity(int velocity, bool obsticle);

/**
 * @brief Handles incoming data from the controller ESP32.
 *
 * @param mac The MAC address of the sender.
 * @param incomingData The incoming data received.
 * @param len The length of the incoming data.
 */
void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

/**
 * @brief Initializes hardware and communication protocols.
 *
 */
void initate();

/**
 * @brief Checks the sensor reading and updates the movement flag.
 *
 * @param parameters Additional parameters for the function (typically unused).
 */
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

    /**
     *  10000 is added to the data sent from the controller if the data
     * is supposed to be a servo command to distinguish from engine commands.
     * Therefore the data has to be modified before sending the actual
     * command to the servo object.
     */
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