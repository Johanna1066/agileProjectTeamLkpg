# Arduino Joystick Controller Project

This project involves controlling an Arduino Nano ESP32 using joysticks and sending their data via WiFi using the ESP-NOW protocol. The project is structured with object-oriented principles, leveraging namespaces, tasks, and semaphores for efficient handling and communication.

## Table of Contents
- [File Overview](#file-overview)
- [Setup and Installation](#setup-and-installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## File Overview

### Joystick.cpp
This file defines the implementation of the `Joystick` class, which handles joystick input operations.

- **Constructor**: Initializes the joystick with the provided analog pin.
- **Destructor**: Cleans up resources.
- **initiateJoystick()**: Sets up the joystick pin and reads the initial center value.
- **doReading()**: Reads and remaps the joystick value.
- **getValue()**: Returns the current remapped joystick value.

### controllerNamespace.h
This header file defines the `controllerNames` namespace, which encapsulates variables and objects related to the hand-controller functionality.

- `reading`: Stores joystick data for transmission.
- `verticalJoystick`: Instance of `Joystick` for vertical readings, connected to pin A2.
- `horizontalJoystick`: Instance of `Joystick` for horizontal readings, connected to pin A4.
- `myHandle`: Semaphore handle for task synchronization.
- `peerInfo`: Structure for ESP-NOW peer information.
- `broadcastAddress`: MAC address of the receiver unit.

### main.cpp
This file contains the main controller code for the Arduino Nano ESP32.

- **setup()**: Initializes serial communication, joysticks, semaphore, WiFi, and ESP-NOW.
- **loop()**: Empty, as tasks are managed independently.
- **OnDataSent()**: Callback for ESP-NOW data sent event.
- **verticalReadSend()**: Task for reading and sending vertical joystick data.
- **horizontalReadSend()**: Task for reading and sending horizontal joystick data.

## Setup and Installation

### Hardware Requirements
- Arduino Nano ESP32
- Two joysticks connected to analog pins A2 and A4
- WiFi network for ESP-NOW communication

### Software Requirements
- Arduino IDE
- ESP32 board support installed in the Arduino IDE
- Required libraries: `esp_now`, `WiFi`, `semphr`

### Installation Steps

1. **Clone the Repository:**
   ```sh
   git clone https://github.com/Johanna1066/agileProjectTeamLkpg/
2. **Open the Project in the Arduino IDE:**
Open the .ino file from the cloned repository in the Arduino IDE.

3. **Connect your Arduino Nano ESP32 to your computer.**

4. **Compile and Upload the Code:**
Compile and upload the main.cpp file to the Arduino Nano ESP32.

**5. !!!!!!!!!!!!!!!!!!!!!!!!!!!!GÖR BILKOD elelr hämta elelr repo något!!!!!!!!!!!!!!!!!!!!!!!**

## Usage
### Initialization
1. Ensure the joystick hardware is properly connected to the specified analog pins (A2 and A4).
2. Power on the Arduino Nano ESP32.
### Operation
    - The vertical and horizontal joystick values will be read and sent to the receiver Arduino Nano ESP32 using the ESP-NOW protocol.
    - Monitor the serial output for status messages related to ESP-NOW transmission.
## Contributing
Contributions are welcome! Please follow these steps to contribute:

1. Fork the repository.
2. Create your feature branch (git checkout -b feature/AmazingFeature).
3. Commit your changes (git commit -m 'Add some AmazingFeature').
4. Push to the branch (git push origin feature/AmazingFeature).
5. Open a pull request.

## Acknowledgements
Special thanks to John.

For more information, visit the project repository.
