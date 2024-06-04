/*
 * The sensor class is responsible for controlling the ultra sonic sensors
 * of the car. The members sensorTriggerPIN and sensorRecieverPIN are the
 * hardware connection and need to be given when a sensor object is created.
 *
 * distance(int) is the value of the latest reading of the sensor
 * and is a distance in cm.
 */
class USsensor
{
private:
    int sensorTriggerPIN;
    int sensorRecieverPIN;

    long distance{};

public:
    USsensor(int triggerPIN, int recieverPIN);

    /*does all of the necessary electronic setup for the hardware
    to work properly.*/
    void initiateUSsensor();

    // returns the most current sensor reading.
    long getDistance();

    // does a new reading of the sensor and updates distance.
    void readDistance();
};
