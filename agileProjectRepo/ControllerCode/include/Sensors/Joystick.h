/*
Joystick class
Each object of the Joystick class controlls one joystick direction.

joystickAnalogPIN is the pin of the joystick Axis the object is going to read values from.
currentValue is used in method doReading to set the current value
initialCenter used once in initiateJoystick 
    We only use this because our joystick gave us odd center values and could sometimes give us +/- 10% of the value we had last time we used the program.

Joystick have three methods; initiateJoystick, used in setup and uses the joystickAnalogPIN to assaign PIN to joystick
                             doReading, sets currentValue based on joystick value and remaps it according to our map
                             getValue, returns currentValue
*/

class Joystick
{
private:
    int joystickAnalogPIN{};
    int currentValue{};
    int initialCenter{};
public:
    Joystick(int pinIN);

    ~Joystick();

    void initiateJoystick();

    void doReading();

    int getValue();
};

Joystick::Joystick(int pinIN)
{
    joystickAnalogPIN = pinIN;
}

Joystick::~Joystick()
{
}

void Joystick::initiateJoystick()
{
    pinMode(joystickAnalogPIN, INPUT);
    initialCenter = analogRead(joystickAnalogPIN); // TODO: kalibrera om genom att trycka på knappen?
}

void Joystick::doReading()
{
    int read = analogRead(joystickAnalogPIN);

    /*
    Create Arduino map()
    long map(long x, long in_min, long in_max, long out_min, long out_max)
    x is input value
    in_min is current lowest input value aviable
    in_max is current max input value aviable
    out_min is new lowest allowed value aviable
    out_max is new max allowed value aviable
    */
    if (read <= initialCenter)
    {
        currentValue = map(read, 0, initialCenter, 0, 2048);
    }
    else
    {
        currentValue = map(read, initialCenter, 4095, 2049, 4095);
    }
}

int Joystick::getValue()
{
    return currentValue;
}
