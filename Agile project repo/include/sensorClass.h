class Sensor
{
private:
    /* data */
public:
    Sensor(/* args */);
    ~Sensor();
};

Sensor::Sensor(/* args */)
{
}

Sensor::~Sensor()
{
}

//------USSensor---------

class USsensor : public Sensor
{
private:
    int distance{};

public:
    USsensor(/* args */);
    ~USsensor();

    void setDistance();
    void initiateSensor();
    void readDistance();

    // IDEA: Setup subscription function
};

USsensor::USsensor(/* args */)
{
}

USsensor::~USsensor()
{
}

void setDistance()
{
}

void initiateSensor()
{
}

void readDistance()
{
}

//------Joystick---------

class joyStick : public Sensor
{
private:
    int verticalValue{};
    int horizontalValue{};
    int buttonValue{};

public:
    void vertialRead();
    void horizontalRead();
    void buttonRead();

    joyStick(/* args */);
    ~joyStick();

    // IDEA: Setup subscription function
};

void vertialRead()
{
}
void horizontalRead()
{
}
void buttonRead()
{
}

joyStick::joyStick(/* args */)
{
}

joyStick::~joyStick()
{
}
