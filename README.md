# Car Arduino Project for 'Arduino Nano ESP32'

This project involves using an 'Arduino Nano ESP32' to control a car. The code employs object-oriented programming principles to manage the car's components, including steering, velocity, and obstacle detection.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Components](#components)
- [Setup](#setup)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## Introduction
This project provides code for an 'Arduino Nano ESP32' to control a car's steering, engine, and sensors. The implementation includes various objects and tasks to handle different functionalities such as steering, velocity control, obstacle detection, and communication using the ESP-NOW protocol.

## Features
- **Steering Control**: Uses `SteeringServo` objects assigned to specific pins.
- **Velocity and Direction Control**: Uses `Engine` objects assigned to specific pins.
- **Obstacle Detection**: Uses `USsensor` objects to ensure there are no obstacles blocking the car's path.
- **Sensor Data Handling**: Includes tasks for reading and handling sensor data.
- **ESP-NOW Communication**: Receives data from the controller Arduino Nano ESP32 using the ESP-NOW protocol.

## Components
- Arduino Nano ESP32
- SteeringServo
- Engine
- USsensor (Ultrasonic Sensor)
- Other necessary components for car assembly

## Setup
1. **Clone the Repository**
   ```sh
   git clone https://github.com/Johanna1066/agileProjectTeamLkpg/
2. **Open the Project in Arduino IDE**
Open the .ino file from the cloned repository in the Arduino IDE.

3. **Install Required Libraries**
Ensure you have the following libraries installed:

-Arduino.h
-esp_now.h
-WiFi.h
-ESP32Servo.h
 
4. **Upload the Code**
Connect your Arduino Nano ESP32 to your computer and upload the code.





5.!!!!!!!!!!!!!!!!!!!!!!! **Download this other repo aswell for the controller**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1







## Usage
Once the setup is complete and the code is uploaded:

1. Power on your Arduino Nano ESP32.
2. The system will initialize the components and start the task for sensor checking.
3. The car's steering and engine will be controlled based on the sensor data and commands received via ESP-NOW from the controller.

## Contributing
Contributions are welcome! Please follow these steps to contribute:

1. Fork the repository.
2. Create your feature branch (git checkout -b feature/AmazingFeature).
3. Commit your changes (git commit -m 'Add some AmazingFeature').
4. Push to the branch (git push origin feature/AmazingFeature).
5. Open a pull request.
6. 

## Acknowledgements
Special thanks to John.

For more information, visit the project repository.
