#include "SmoothJoystick.h"
#include "UpdateRegistry.h"
#include "612.h"
#include "main.h"

#include <cmath>

SmoothJoystick::SmoothJoystick(UINT32 a) : Joystick(a) 
{
    robot->updateRegistry.add(this, &updateHelper);
}

SmoothJoystick::~SmoothJoystick() 
{
    
}

void SmoothJoystick::pushBtn(unsigned int btn, obj o, helpFunc h) 
{
    Handler handler={o,h,btn,false};
    handlers.push_back(handler);
}

void SmoothJoystick::updateSJ() 
{
    for (unsigned int f = 0; f < NUMBUTTONS; f++)
    {
        for (unsigned int s = 1; s < WAIT_TIME; s++)
        {
            buttons[f][s - 1] = buttons [f][s];
        }
        buttons[f][WAIT_TIME - 1] = Joystick::GetRawButton(f+1);
    } 
    for (unsigned int x = 0; x < handlers.size(); x++) 
    {
        Handler handler = handlers[x];
        bool btnState = GetRawButton(handler.btnNumber);
        if(btnState && !handler.prevState) 
        {
            callHandler(x);
            handler.prevState = true;
        } 
        else if (!btnState) 
        {
            handler.prevState = false;
        }
    }
}

void SmoothJoystick::updateHelper(obj o) {
    ((SmoothJoystick*)(o)) -> updateSJ();
}

Trigger SmoothJoystick::GetTriggerState() 
{
    float value=GetRawAxis(TRIGGER_AXIS);
    if(value<TRIGGER_TOLERANCE-1) 
    {
        return TRIG_R;
    } 
    else if(value>1-TRIGGER_TOLERANCE) 
    {
        return TRIG_L;
    }
    return TRIG_NONE;
}

void SmoothJoystick::callHandler(unsigned int x) 
{
    Handler handler = handlers[x];
    handler.callback(handler.param,handler.btnNumber);
}

bool SmoothJoystick::GetRawButton(UINT32 btn) 
{
    for (unsigned int i = 0; i < WAIT_TIME; i++)
    {
        if (!buttons[btn - 1][i])
        {
           return false;
        }
    }
    return true;
}

bool SmoothJoystick::IsAxisZero(unsigned int btn) {
    return (fabs(Joystick::GetRawAxis(btn)) < TRIGGER_TOLERANCE);
}

