#include "steeringFunctions.h"

// Car code

void sensorCheck(void *parameters);
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
void sensorCheck(void *parameters);
void initate();

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
