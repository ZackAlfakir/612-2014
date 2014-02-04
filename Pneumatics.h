#ifndef Pneumatics_H
#define Pneumatics_H

#include <DoubleSolenoid.h>
#include <Timer.h>
#include <Relay.h>
#include <DigitalInput.h>
#include "Controls.h"
//#include "main.h"
#include "ports.h"
#include "612.h"

class Pneumatics
{
public:
    Pneumatics::Pneumatics();
    void runPneumatics(int pnum);
    void toggleSolenoid(DoubleSolenoid* sol);
    void pressurize();
private:
    DoubleSolenoid* shift1;//8,7
    DoubleSolenoid* clamp; //6,5
    //DoubleSolenoid* solenoids[2];
    //DoubleSolenoid* shift2;
    float axis;
    //Relay* compressor;
    //DigitalInput* digiSwitch;
    
};

#endif
