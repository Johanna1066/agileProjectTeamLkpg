#include <Arduino.h>
#define ENA_PIN A1           // The Arduino Nano ESP32 pin connected to the ENA pin L298N
#define IN1_PIN D6           // The Arduino Nano ESP32 pin connected to the IN1 pin L298N
#define IN2_PIN D5
#define ENB_PIN A2
#define IN3_PIN D4
#define IN4_PIN D3 




const int Xin = A6;
const int Yin = A5;
int motorValue = {};
int stickCenter = {};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins as outputs.
  Serial.begin(9600);
 
  stickCenter = 52;
  //pinMode(Yin, INPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  delay(1000);
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(ENA_PIN, 255);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  analogWrite(ENB_PIN, 255);

  delay(1000);
  analogWrite(ENB_PIN, 120);

  delay(1000);
  analogWrite(ENA_PIN, 120);
  analogWrite(ENB_PIN, 255);

 


  
  

  
  
  /* Testing for Joystickstuff
  int xval = analogRead (Xin);
  int Yval = analogRead (Yin);

  motorValue = map(Yval, 0, 4095, 200, 0); //Mappad bakofram?
 Serial.println(motorValue); 


 if ((stickCenter - 10) < stickCenter < (stickCenter + 10)){
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
    analogWrite(ENA_PIN, 0);
 }
 if (motorValue > (stickCenter + 10)){ //FORWARD
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, HIGH);
    analogWrite(ENA_PIN, 750);
 }
 if (motorValue > (stickCenter - 10)){ //REVERSE
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    analogWrite(ENA_PIN, 750);
 }

delay(500);

  if (motorValue < 195){
    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    analogWrite(ENA_PIN, motorValue);
    delay(1000);
    Serial.println(motorValue);
  }

  else if (motorValue > 500){
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, HIGH);
    analogWrite(ENA_PIN, motorValue);
    delay(20);
    Serial.println(motorValue);
  }
  else if (200 < motorValue < 500){
    analogWrite(ENA_PIN, 0);
  }
  */
}
