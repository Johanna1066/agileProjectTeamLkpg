#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <vector>


#include "Sensors/USsensor.h"
#include "Motors/Engine.h"
#include "Motors/SteeringServo.h"
#include "steeringFunctions.h"


#include "semphr.h"


// Car code


//Handle för att styra engine
SemaphoreHandle_t engineHandle;


void sensorCheck(void* parameters);



// Comunication code


// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&dataRecieved, incomingData, sizeof(dataRecieved));
  
  /*TODO: if(dataRecieved matchar enginedata)
  {
    semaphoreTAKE
    gör data användbar
    skicka info till engines
    semaphoreGIVE
  }
  else if (dataRecieved matchar servodata)
  {
    gör data användbar
    skicka info till servo
  }
  */ 
}



void setup()
{
  // Init Serial Monitor
  Serial.begin(115200);
  // Create semaphore
  engineHandle = xSemaphoreCreateMutex();
  if (engineHandle == NULL)
  {
    Serial.println("Error creating semaphore");
    return;
  }

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);


  // Create tasks

  if (xTaskCreate(
          sensorCheck,
          "*sensorCheck",
          4096,
          NULL,
          1,
          NULL) != pdPASS)
  {
    Serial.println("Error creating task");
    return;
  }
  
}

void loop()
{

}


void sensorCheck(void* parameters)
{
  mySensor.readDistance();
  reading = mySensor.getDistance();

  if (reading < 20) //TODO: kan detta läggas in i USsensorklassen istället för hårdkodning? exempelvis i konstruktorn
  {
    //TODO: Semaphore TAKE
    
    //Hinder forward movement någonting någonting

    //TODO: Semaphore GIVE
  }
}

