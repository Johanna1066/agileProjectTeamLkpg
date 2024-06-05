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
    // reading: Stores the data from the joysticks to be sent to the receiver Arduino.
    int reading{};
    // verticalJoystick(int): Joystick object for vertical joystick readings, connected to analog pin.
    Joystick verticalJoystick(A2);
    // horizontalJoystick(int): Joystick object for horizontal joystick readings, connected to analog pin.
    Joystick horizontalJoystick(A4);
    // myHandle: Semaphore handle for task synchronization and protection of shared resources.
    SemaphoreHandle_t myHandle;
    // peerInfo: Structure containing information about the ESP-NOW peer for WiFi communication.
    esp_now_peer_info_t peerInfo;
    // broadcastAddress: MAC address of the receiver unit this unit is trying to connect to (replace with your receiver's MAC address).
    uint8_t broadcastAddress[] = {0xEC, 0xDA, 0x3B, 0x60, 0xCD, 0xB4};
}