#ifndef _WCC_STEERINGFUNCTIONS_H
#define _WCC_STEERINGFUNCTIONS_H

/**
 * Header file containing all of the function declarations
 * used by main.cpp to run the car.
 */

#include <Arduino.h>

void setEnginesVelocity(int velocity, bool obsticle);

void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

void initiate();

void sensorCheck(void *parameters);

#endif //_WCC_STEERINGFUNCTIONS_H