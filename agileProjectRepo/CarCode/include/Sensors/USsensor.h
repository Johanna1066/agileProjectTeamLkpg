#pragma once
//------USSensor---------

class USsensor
{
private:
    int sensorTriggerPIN;
    int sensorRecieverPIN;

    long distance{};
    long messurement{};

public:
    USsensor(int triggerPIN, int recieverPIN);
    ~USsensor();
    void initiateUSsensor();
    long getDistance();
    void readDistance();
};

USsensor::USsensor(int triggerPIN, int recieverPIN)
{
    sensorTriggerPIN = triggerPIN;
    sensorRecieverPIN = recieverPIN;
}

USsensor::~USsensor()
{
    /*
    delete sensorTriggerPIN;
    delete sensorRecieverPIN;

    delete distance;
    */
}

void USsensor::initiateUSsensor()
{
    pinMode(sensorTriggerPIN, OUTPUT);
    pinMode(sensorRecieverPIN, INPUT);
}

long USsensor::getDistance()
{
    return distance;
}

// IDEA: Setup subscription function

void USsensor::readDistance()
{
    // TODO: Can we remove or change theese delays in some way?
    // We don't want to hard code in delays
    digitalWrite(sensorTriggerPIN, LOW);
    vTaskDelay(5 / portTICK_PERIOD_MS);
    digitalWrite(sensorTriggerPIN, HIGH);
    vTaskDelay(10 / portTICK_PERIOD_MS);
    digitalWrite(sensorTriggerPIN, LOW);

    pinMode(sensorRecieverPIN, INPUT);

    messurement = pulseIn(sensorRecieverPIN, HIGH);

    distance = (messurement / 2) / 29.1; // Convert distance to cm
}