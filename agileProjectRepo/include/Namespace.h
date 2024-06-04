namespace controllerNames{
    int reading{};
    Joystick verticalJoystick(A2);
    Joystick horizontalJoystick(A4);
    SemaphoreHandle_t myHandle;
    esp_now_peer_info_t peerInfo;
    uint8_t broadcastAddress[] = {0xEC, 0xDA, 0x3B, 0x60, 0xCD, 0xB4};  // REPLACE WITH YOUR RECEIVER MAC Address
}