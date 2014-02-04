#include "Pneumatics.h"
#include "main.h"
//#include <Relay.h>

Pneumatics::Pneumatics()
{
    shift1 = new DoubleSolenoid(SHIFT_MOD,SHIFT_CHAN_F,SHIFT_CHAN_R);
    clamp = new DoubleSolenoid(CLAMP_MOD,CLAMP_PORT_1,CLAMP_PORT_2);
    
//     compressor = new Relay(PNUM_RELAY_MODULE, PNUM_RELAY_CHANNEL);
//     digiSwitch = new DigitalInput(PNUM_DIGIN_MODULE, PNUM_DIGIN_CHANNEL);
}

void Pneumatics::runPneumatics(int pnum)
{
    static int prevPnum = -1;
//     bool isNotified = false;
    pressurize();
    unsigned long int prevVal = 0;
    if (pnum == 0)
    {
        toggleSolenoid(shift1);
        if (prevPnum != pnum)
        {
            std::printf("Shift Solenoid");
        }
    }
    else if (pnum == 1)
    {
        toggleSolenoid(clamp);
        if (prevPnum != pnum)
        {
            std::printf("Clamp Solenoid\n");
        }
    }
    else if (pnum == 2)
    {
        if (robot->sense->pnumSwitch->Get() != prevVal)
        {
            std::printf("DigitalInput: %ld\n", robot->sense->pnumSwitch->Get()); 
        }
    }
    else if(pnum >= 3)
    {
        std::printf("MAX");
        robot->selection = 20;
    }
    prevPnum = pnum;
}
void Pneumatics::toggleSolenoid(DoubleSolenoid* sol)
{
    axis = robot->driverJoy->GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
    static DoubleSolenoid::Value solToggled = DoubleSolenoid::kOff;
    if (axis > JOYSTICK_ZERO_TOLERANCE)
    {
        sol->Set(DoubleSolenoid::kForward);
        if (solToggled != DoubleSolenoid::kForward)
        {
            std::printf("Solenoid Forward\n");
            solToggled = DoubleSolenoid::kForward;
        }
    }
    else if (axis < JOYSTICK_ZERO_TOLERANCE*-1)
    {
        sol->Set(DoubleSolenoid::kReverse);
        if (solToggled != DoubleSolenoid::kReverse)
        {
            std::printf("Solenoid Reverse\n");
            solToggled = DoubleSolenoid::kReverse;
        }
    }
    else
    {
        sol->Set(DoubleSolenoid::kOff);
        if (solToggled != DoubleSolenoid::kOff)
        {
            std::printf("Solenoid Off");
            solToggled = DoubleSolenoid::kOff;
        }
    }
}
void Pneumatics::pressurize()
{
    if (robot->sense->pnumSwitch->Get() == 0)
    {
        robot->motors->compressor->Set(Relay::kForward);
    }
    else
    {
        robot->motors->compressor->Set(Relay::kOff);
    }
}

