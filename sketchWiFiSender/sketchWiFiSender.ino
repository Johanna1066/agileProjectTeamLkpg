/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/communication-between-two-esp32
 */

// ESP32: TCP CLIENT + A BUTTON/SWITCH
#include <WiFi.h>
#include <Arduino.h>

int yLedJoystick = A1;
int yAxisVal = 2000;


const char* ssid = "Chokladboll";     // CHANGE TO YOUR WIFI SSID
const char* password = "Vilseberga"; // CHANGE TO YOUR WIFI PASSWORD
const char* serverAddress = "192.168.0.112"; // CHANGE TO ESP32#2'S IP ADDRESS
const int serverPort = 4080;

int x = 0;

WiFiClient TCPclient;

void setup() {
  Serial.begin(9600);

  Serial.println("ESP32: TCP CLIENT + A BUTTON/SWITCH");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // connect to TCP server (Arduino #2)
  if (TCPclient.connect(serverAddress, serverPort)) {
    Serial.println("Connected to TCP server");
  } else {
    Serial.println("Failed to connect to TCP server");
  }

  pinMode(yLedJoystick, INPUT);
}

void loop() {

  if (!TCPclient.connected()) {
    Serial.println("Connection is disconnected");
    TCPclient.stop();

    // reconnect to TCP server (Arduino #2)
    if (TCPclient.connect(serverAddress, serverPort)) {
      Serial.println("Reconnected to TCP server");
    } else {
      Serial.println("Failed to reconnect to TCP server");
    }
  }

  yAxisVal = analogRead(yLedJoystick);
  Serial.println(yAxisVal);
  
  if(yAxisVal < 1000){
    TCPclient.write('1');
    TCPclient.flush();
  }
  else{
    TCPclient.write('0');
    TCPclient.flush();
  }
/*
  if (x < 5) {
    TCPclient.write('1');
    TCPclient.flush();
    Serial.println("- The button is pressed, sent command: 1");
    x++;
  }

  if (5 <= 5) {
    TCPclient.write('0');
    TCPclient.flush();
    Serial.println("- The button is released, sent command: 0");
    x++;
  }
  if(x == 10)
  x = 0;
  */
}
