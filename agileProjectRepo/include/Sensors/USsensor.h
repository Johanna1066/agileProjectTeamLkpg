/**
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
    /**
     * @brief Constructs a USsensor object.
     *
     * @param triggerPIN The pin number for triggering the sensor.
     * @param receiverPIN The pin number for receiving the sensor's echo.
     */
    USsensor(int triggerPIN, int recieverPIN);

    /**
     * @brief Initializes the ultrasonic sensor.
     *
     */
    void initiateUSsensor();

    /**
     * @brief Gets the most current sensor reading.
     *
     * @return The most recent distance reading in centimeters.
     */
    long getDistance();

    /**
     * @brief Performs a new reading of the sensor and updates the distance.
     *
     * This function triggers the sensor, waits for the echo, and updates the
     * distance member with the new reading.
     */
    void readDistance();
};
