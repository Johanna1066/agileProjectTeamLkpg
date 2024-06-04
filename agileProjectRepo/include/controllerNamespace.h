/*
Namespace for hand-controller
reading; used to store data from joystick and send data to receiver arduino
verticalJoystick; A joystick object that is used to get vertical joystick readings
horizontalJoystick; A joystick object that is used to get horizontal joystick readings
myHandle; A handle that locks task and makes tasks unable change certain variables without having access to this handle
peerInfo; Handles info about WiFi communication
broadcastAddress; is the MAC address this unit is trying to connect to
*/
namespace controllerNames{
    int reading{};
    Joystick verticalJoystick(A2);
    Joystick horizontalJoystick(A4);
    SemaphoreHandle_t myHandle;
    esp_now_peer_info_t peerInfo;
    uint8_t broadcastAddress[] = {0xEC, 0xDA, 0x3B, 0x60, 0xCD, 0xB4};  // REPLACE WITH YOUR RECEIVER MAC Address
}