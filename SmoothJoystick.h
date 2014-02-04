#ifndef SMOOTH_JOYSTICK_H
#define SMOOTH_JOYSTICK_H

#include <Joystick.h>
#include "Controls.h"
#include <vector>
#include <bitset>


class SmoothJoystick : public Joystick 
{
public:
    static const float JOYSTICK_ZERO_TOLERANCE = 0.1;
    SmoothJoystick(UINT32);
    ~SmoothJoystick();
    bool GetRawButton(UINT32 btn);
    bool IsAxisZero(unsigned int);
    Trigger GetTriggerState();
    typedef void* obj;
    typedef void(*helpFunc)(obj,unsigned int);
    void pushBtn(unsigned int,obj,helpFunc);
    void updateSJ();
    
    typedef void* obj;
    typedef void(*funcName)(obj);
    static void updateHelper(obj);
    
private:
    struct Handler {
        obj param;
        helpFunc callback;
        unsigned int btnNumber;
        bool prevState;
    };
    const static unsigned int NUMBUTTONS = 12;
    const static unsigned int WAIT_TIME = 3;
    std::bitset<WAIT_TIME> buttons[NUMBUTTONS];
    void callHandler(unsigned int);
    std::vector<Handler> handlers;
};

#endif 
