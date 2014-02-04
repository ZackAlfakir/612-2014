#ifndef MOTORS_H
#define MOTORS_H

#include <vector>

#include <SpeedController.h>
#include <Talon.h>
#include <CANJaguar.h>
#include <Relay.h>

#include "ports.h"
#include "SmoothJoystick.h"
#include "Controls.h"

enum motor_type
{
    TALON,
    CANJAG,
    RELAY
};

struct motor_info
{
    const char* name;
    motor_type type;
    uint8_t module;
    uint32_t channel;
    void* relay;
};

class Motors
{
public:
    Motors::Motors();
    Motors::~Motors();
    void runMotor(int motor);
    void disable();
    motor_info mot;
    std::vector<motor_info> motors;
    Relay* compressor; //Spike 1,1
    void setTalon(Talon* t, bool print, int motor);
    void setTalon(int motor, bool print);
    Talon* drivetrain[4];
private:
    //SmoothJoystick* joy;
    float joy;
    float power;
    float left;
    float right;
    void drive(bool print);
    void drive2(bool print);

    Talon* FR; //Talon 7
    Talon* FL; //Talon 1
    Talon* RR; //Talon 6
    Talon* RL; //T2
    
    Talon* grabber; //Talon 3
    
    CANJaguar* tilt; //CANJag 1
};
#endif
