#ifndef _WCC_CONTROLLERNAMESPACE_H
#define _WCC_CONTROLLERNAMESPACE_H

/*
 * Namespace for hand-controller
 * This namespace encapsulates all the variables and objects related to the hand-controller functionality.
 * 
 * reading: Stores the data read from the joysticks, which will be sent to the receiver Arduino.
 * verticalJoystick: An instance of the Joystick class used to get readings from the vertical joystick (connected to analog pin A2).
 * horizontalJoystick: An instance of the Joystick class used to get readings from the horizontal joystick (connected to analog pin A4).
 * myHandle: A semaphore handle that ensures task synchronization and protects shared resources by preventing certain variables from being modified without access to this handle.
 * peerInfo: A structure that holds information about the ESP-NOW peer, used for WiFi communication.
 * broadcastAddress: The MAC address of the receiver unit that this unit is trying to connect to (replace with your specific receiver's MAC address).
 */
namespace controllerNames {
    int reading{};

    Joystick verticalJoystick(A2);

    Joystick horizontalJoystick(A4);

    SemaphoreHandle_t joystickHandle;

    esp_now_peer_info_t peerInfo;

    uint8_t broadcastAddress[] = {0xEC, 0xDA, 0x3B, 0x60, 0xCD, 0xB4};
}

#endif //_WCC_CONTROLLERNAMESPACE_H