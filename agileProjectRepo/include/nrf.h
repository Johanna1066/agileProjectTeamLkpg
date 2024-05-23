//#ifndef NRF_H_
//#define NRF_H_

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ESP32Servo.h>

const byte addressRF_RECIEVE[6] = "00001"; // address of nrf recieve part. it is for robot part.
const byte addressRF_SEND[6] = "00001"; // address of nrf send part. it is for contoller part.

#define RECIEVE_RF 1 // if the nrf in recieve mode
#define SEND_RF 0 // if the nrf in send mode

class NRF // NRF24L01 wifi module class definition
{
private:

public:
    int CE_PIN;
    int CSN_PIN;
    byte address[6];
    int PA_LEVEL;
    int LISTEN_OR_NOT;
    NRF(int a, int b, const byte c[6], int d, int e);
    RF24 setupNRF();
    void sendPacket(char *packet, int numOfByte, RF24 radio);
    void recievePacket(char *packet, int numOfByte, RF24 radio);
};

//#include "nrf.h"

NRF::NRF(int a, int b, const byte c[6], int d, int e) // this method is for assigning the pins and address of NRF module
{
    CE_PIN = a;
    CSN_PIN = b;
    for(int i = 0; i < 6; i++){
        address[i] = c[i];
    }
    PA_LEVEL = d;
    LISTEN_OR_NOT = e;
}


RF24 NRF::setupNRF() // this method is for set the NRF parameters and mode of NRF like transmitter or reciever.
{

  RF24 radio(NRF::CE_PIN, NRF::CSN_PIN);
  radio.begin();
  radio.openReadingPipe(0, NRF::address);
  radio.setPALevel(NRF::PA_LEVEL);
  if (NRF::LISTEN_OR_NOT == 1)
  {
    radio.startListening();
  }
  else
  {
    radio.stopListening();
  }
  return radio;
}

void NRF::sendPacket(char *packet, int numOfByte, RF24 radio) // this method is for sending the packet command using the nrf module
{
  radio.write(packet, numOfByte);
}

void NRF::recievePacket(char *packet, int numOfByte, RF24 radio) // this method is for recieving the packet command using the nrf module
{
  radio.read(packet, numOfByte);
}

//#endif // !NRF_H_