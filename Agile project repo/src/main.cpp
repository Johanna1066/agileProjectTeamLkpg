// Include the Servo library 
#include <ESP32Servo.h> 
#include <Arduino.h>
// Declare the Servo pin 

// Create a servo object 

void setup() { 
   // We need to attach the servo to the used pin number 
   Serial.begin(9600);
}
void loop(){ 
   Serial.write("apa\n");
}