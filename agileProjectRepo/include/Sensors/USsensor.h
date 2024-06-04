
/*
The sensor class is responsible for controlling the ultra sonic sensors
 of the car. The members sensorTriggerPIN and sensorRecieverPIN are the
 hardware connection and need to be given when a sensor object is created.

distance(int) keeps track of the value of the latest reading of the sensor
 and is a distance in cm.

 The class has three methods:
            initiateSensor - does all of the necessary electronic setup for the
                             hardware to work properly.
               getDistance - returns the most current sensor reading.
              readDistance - does a new reading of the sensor and updates distance.

*/

class USsensor
{
private:
    int sensorTriggerPIN;
    int sensorRecieverPIN;

    long distance{};

public:
    USsensor(int triggerPIN, int recieverPIN);
    void initiateUSsensor();
    long getDistance();
    void readDistance();
};


