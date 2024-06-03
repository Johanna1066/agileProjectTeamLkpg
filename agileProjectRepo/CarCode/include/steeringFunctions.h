#pragma once

/*
Header file containing all of the funtions and globlal variables
used by main.cpp to run the car.

setEnginevelocity(int velocity, bool obsticle) - loops thorugh the vector of engine objects and sets all
                                                 their velocities to the inargument velocity.


OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) - function that runs when the controller sends
                                                 any data to the car. Depending on the data recieved it's either
                                                 handled as a engine command or it's handled as a servo command.



intitate - Initiate runs at the start of setup() in main.cpp and makes sure that the hardware, the communcations
 and the mutex handles are all initiated.




sensorcheck




*/

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

void setEnginesVelocity(int velocity, bool obsticle)
{
    for (auto &engine : engines)
    {
        engine.setVelocity(velocity, obsticle);
    }
}

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
    esp_now_register_recv_cb(OnDataRecv);
}

void sensorCheck(void *parameters)
{
    for (;;)
    {
        mySensor.readDistance();
        reading = mySensor.getDistance();

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