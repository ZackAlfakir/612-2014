#include "Shifter.h"
#include "612.h"
#include "main.h"

Shifter::Shifter(uint8_t mod,uint32_t chanF,uint32_t chanR)
{
    shifter=new DoubleSolenoid(mod,chanF,chanR);
    //TODO
}

Shifter::~Shifter()
{
    delete shifter;
    //TODO
}

void Shifter::shiftGear()
{
    if(gear == low)
    {
        
        setHigh();
    }
    else if(gear == high)
    {
        
        setLow();
    }
}

void Shifter::setHigh()
{
    gear=high;
    robot->pnum->setVectorValues(TIME, shifter, DoubleSolenoid::kForward);
}

void Shifter::setLow()
{
    gear=low;
    robot->pnum->setVectorValues(TIME, shifter, DoubleSolenoid::kReverse);
}