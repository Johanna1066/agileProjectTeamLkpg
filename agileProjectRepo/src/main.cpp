/*



*/

#include "steeringFunctions.h"




void sensorCheck(void *parameters);


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
