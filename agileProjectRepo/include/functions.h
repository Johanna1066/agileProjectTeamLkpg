#ifndef _WCC_FUNCTIONS_H
#define _WCC_FUNCTIONS_H

#include <Arduino.h>
#include <esp_now.h>

void initiate();

void horizontalReadSend(void *parameters);
void verticalReadSend(void *parameters);

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

#endif //_WCC_FUNCTIONS_H