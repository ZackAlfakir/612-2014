#ifndef CONTROLS_H
#define CONTROLS_H

typedef unsigned int Button;
typedef unsigned int Axis;

enum Trigger 
{
    TRIG_NONE = 0,
    TRIG_L = -1,
    TRIG_R = 1
};

static const float DRIVE_POWER = 1.0;

static const float JOYSTICK_ZERO_TOLERANCE = 0.1;
static const float TRIGGER_TOLERANCE = 0.25;
static const Axis TRIGGER_AXIS = 3; //may need to rename this later
//TODO Rumble

static const unsigned int DRIVER_JOY = 1;
static const unsigned int GUNNER_JOY = 2;

static const Button BUTTON_A               = 1;
static const Button BUTTON_B               = 2; 
static const Button BUTTON_X               = 3;
static const Button BUTTON_Y               = 4; 
static const Button BUTTON_L1              = 5;
static const Button BUTTON_R1              = 6;
static const Button BUTTON_BACK            = 7; 
static const Button BUTTON_START           = 8;
static const Button BUTTON_LEFT_JOY_CLICK  = 9;
static const Button BUTTON_RIGHT_JOY_CLICK = 10;

static const Axis LEFT_JOYSTICK_X          = 1;
static const Axis LEFT_JOYSTICK_Y          = 2; 
//not sure what to do for the triggers
static const Axis RIGHT_JOYSTICK_X         = 4;
static const Axis RIGHT_JOYSTICK_Y         = 5;
static const Axis DPAD                     = 6;

//Button declarations
static const Button SHIFT_LOW              = BUTTON_L1; 
static const Button SHIFT_HIGH             = BUTTON_R1; 

static const Button BUTTON_CLAMP_DOWN      = BUTTON_A;
static const Button BUTTON_CLAMP_UP        = BUTTON_B;

static const Button BUTTON_GRAB            = BUTTON_X;
//static const Button BUTTON_TILT_UP         = BUTTON_Y; 

//Axis declarations
static const Axis DRIVER_LEFT_DRIVE_AXIS   = LEFT_JOYSTICK_Y;
static const Axis DRIVER_RIGHT_DRIVE_AXIS  = RIGHT_JOYSTICK_Y;

//Copied post from XBOX thread
/*
Buttons
01: A (green/bottom)
02: B (red/right)
03: X (blue/left)
04: Y (yellow/top)
05: Left Bumper (L1)
06: Right Bumper (R1)
07: Back (left)
08: Start (right)
09: Left Joystick Click
10: Right Joystick Click

Axes
01: Left Joystick X: -left, +right
02: Left Joystick Y: -up, +down
03: Triggers (L2/R2): -right, +left, 0 at rest, 0 if both pressed
04: Right Joystick X: -left, +right
05: Right Joystick Y: -up, +down
06: DPad X: -left, +right
*/
//no D-Pad Y axis



#endif
