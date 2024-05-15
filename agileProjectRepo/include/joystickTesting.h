#include <Arduino.h>

//PINS
int inX = A4;
int inY = A3;
int button = 8;

int centerXvalue {};
int centerYvalue{};

int xAxisVal {};
int yAxisVal{};

void initiateJoystickTesting(){
    Serial.begin (9600); 
    pinMode(inX, INPUT);
    pinMode(inY, INPUT);
    pinMode(button, INPUT);
    centerXvalue = analogRead(inX);
    centerYvalue = analogRead(inY);
}

void loopJoystickTesting(){

    xAxisVal = analogRead (inX);   //analog value between 0 - 4095
    yAxisVal = analogRead(inY);

    if((centerXvalue - 100) <= xAxisVal && xAxisVal <= (centerXvalue + 100))
    {
    Serial.println("X axis Center.");
    }
    else
    {
    Serial.print("X = ");
    Serial.println (xAxisVal);
    }

    if((centerYvalue - 100) <= yAxisVal && yAxisVal <= (centerYvalue + 100))
    {
    Serial.println("Y axis Center.");
    }
    else
    {
    Serial.print("Y = ");
    Serial.println(yAxisVal);
    }

    delay(1000);

}