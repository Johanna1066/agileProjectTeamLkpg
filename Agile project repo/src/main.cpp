#include <Arduino.h>
#include <ESP32Servo.h>

int inX= A1;        // X axis value from joystick
int inServo = 7;    // DIGITAL pin to servo

int centerXvalue {};

int xAxisVal {};
int servoVal {};

Servo testServo;    // create servo object

void setup ()
{
 Serial.begin (9600); 
 pinMode(inX, INPUT);
 testServo.attach(inServo);     //attach srvo object with pin
 centerXvalue = map(analogRead(inX),  0, 4095, 0, 180);
}

void loop ()
{
 
 xAxisVal = analogRead (inX);   //analog value between 0 - 4095

          // map *något med xAxisVal*, xAxis min - max, turn min - max
 servoVal = map(xAxisVal, 0, 4095, (centerXvalue - 15), (centerXvalue + 20));

 testServo.write(servoVal);


 Serial.print("X = ");
 Serial.println (xAxisVal, DEC);
 Serial.print("map = ");
 Serial.println(servoVal, DEC);


}
