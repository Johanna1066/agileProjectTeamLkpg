
# Car Control System Project

This project focuses on controlling a car using an Arduino Nano ESP32. It integrates steering, velocity, obstacle detection, and communication using the ESP-NOW protocol.

## Table of Contents
- [Features](#features)
- [Components](#components)
- [Setup](#setup)
- [Usage](#usage)
- [Contributing](#contributing)
- [Acknowledgements](#acknowledgements)

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
Open the Project in Arduino IDE
Open the .ino file from the cloned repository in the Arduino IDE.

Install Required Libraries
Required libraries: esp_now.h, WiFi.h, ESP32Servo.h, and semphr.

Upload the Code
Connect your Arduino Nano ESP32 to your computer and upload the code.

Download the Controller Repository
Make sure to download the repository for the controller as well.

Usage
Once the setup is complete and the code is uploaded:

Power on your Arduino Nano ESP32.
The system will initialize the components and start the task for sensor checking.
The car's steering and engine will be controlled based on the sensor data and commands received via ESP-NOW from the controller.
Contributing
Contributions are welcome! Please follow these steps to contribute:

Fork the repository.
Create your feature branch (git checkout -b feature/AmazingFeature).
Commit your changes (git commit -m 'Add some AmazingFeature').
Push to the branch (git push origin feature/AmazingFeature).
Open a pull request.
Acknowledgements
Special thanks to John.

For more information, visit the project repository.
