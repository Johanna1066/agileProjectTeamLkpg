#ifndef CORE_H_
#define CORE_H_

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ESP32Servo.h>
//#include "dist_Sens.h"
#include "nrf.h"
//#include "joy.h"
//#include "servoM.h"
//#include "l298.h"

#endif // !CORE_H_

//#include "core.h"

RF24 radioSend;
RF24 radioRecieve;
Servo ServoMotor;
//DIS_SENSOR DIS_SENSOR_INST(7, 6);
NRF NRF_INST_SEND(7, 6, addressRF_SEND, RF24_PA_LOW, SEND_RF);
NRF NRF_INST_RECIEVE(7, 6, addressRF_RECIEVE, RF24_PA_LOW, RECIEVE_RF);
//JOY JOY_INST(1, INPUT, 2, 3);
//L298 L298_INST(1, 2, 3, 4, 5, 6);
//SERVO_M SERVO_M_INST(1);

char send_packet[4];
char recieve_packet[4];

int counter_wait = 0;

int xValue;
int yValue;
int region;

int lift = 0;

void setup()
{
  Serial.begin(9600);
  //DIS_SENSOR_INST.setupDistSensor();
  radioSend = NRF_INST_SEND.setupNRF();
  radioRecieve = NRF_INST_RECIEVE.setupNRF();
  //JOY_INST.setupSwJoy();
  //L298_INST.L298_Setup();
  //SERVO_M_INST.servo_setup();
}

void loop()
{

  NRF_INST_RECIEVE.recievePacket(recieve_packet, 4, radioRecieve);
  //int distance = DIS_SENSOR_INST.readFromDistSensor();
  Serial.println(12345);
  //JOY_INST.readJoy(xValue, yValue, region);
  //JOY_INST.readSW_joy(lift);
  //L298_INST.L298_WriteData(1, 0, 100, 200);
  //SERVO_M_INST.servo_writeData(ServoMotor, 20);

  send_packet[0] = xValue;
  send_packet[1] = yValue;
  send_packet[2] = region;
  send_packet[3] = lift;

  counter_wait++;

  if(counter_wait == 100){
    NRF_INST_SEND.sendPacket(send_packet, 16, radioSend);
    counter_wait = 0;
  }
}