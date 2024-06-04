/*
*Joystick class
*Each object of the Joystick class controls one joystick direction.
*
*default constructor Joystick(int) requires an arduino PIN to function.
*So Joystick can read and get values from our joystick.
*
*Joystick have 3 methods; initiateJoystick(), doReading(), getValue()
*
*Joystick have 3 private variables; joystickAnalogPIN, currentValue and initialCenter
*/
class Joystick
{
private:
    //joystickAnalogPIN, used in initiateJoystick. Gets its value from constructor Joystick(int PIN)
    int joystickAnalogPIN{};
    //currentValue, saves the joysticks current value in doReading()
    int currentValue{};
    //initialCenter, used to find and map the center value of the joysticks
    int initialCenter{};
public:
    //Joystick(int), saves an int PIN that the object is going to use and read
    Joystick(int pinIN);

    ~Joystick();
    //initiateJoystick(), used in setup and uses the joystickAnalogPIN to assign PIN to joystick
    void initiateJoystick();
    //doReading(), sets currentValue based on joystick value and remaps it according to our map
    void doReading();
    //getValue(), returns currentValue using map
    int getValue();
};