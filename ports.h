#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>
// DriveTrain Modules
const static uint8_t  TALON_FL_MODULE  = 1; //real
const static uint8_t  TALON_FR_MODULE  = 1; //real
const static uint8_t  TALON_RL_MODULE  = 1; //real
const static uint8_t  TALON_RR_MODULE  = 1; //real

// DriveTrain Channels
const static uint32_t TALON_FL_CHANNEL = 1; //real
const static uint32_t TALON_FR_CHANNEL = 6; //real
const static uint32_t TALON_RL_CHANNEL = 2; //real
const static uint32_t TALON_RR_CHANNEL = 7; //real

// Pneumatics Modules
const static uint8_t  PNUM_DIGIN_MODULE  = 1;
const static uint8_t  PNUM_RELAY_MODULE  = 1;

// Pneumatics Channels
const static uint32_t PNUM_DIGIN_CHANNEL = 8;
const static uint32_t PNUM_RELAY_CHANNEL = 8;

// Shifter
const static uint32_t SHIFT_MOD  = 1;
const static uint8_t  SHIFT_CHAN_F = 7;
const static uint8_t  SHIFT_CHAN_R = 8;

// Joystick
const static uint32_t DRIVER_JOY_PORT = 1;
const static uint32_t GUNNER_JOY_PORT = 2;

// Arm values
const static uint32_t TILT_DEV = 1;
const static uint8_t GRAB_MOD = 1;
const static uint32_t GRAB_CHAN = 3;

const static uint8_t CLAMP_MOD = 1;
const static uint32_t CLAMP_PORT_1 = 5;
const static uint32_t CLAMP_PORT_2 = 6;

//Encoders
const uint8_t  LEFT_ENCODER_A_MOD  = 1;
const uint32_t LEFT_ENCODER_A_CHAN = 1;

const uint8_t  LEFT_ENCODER_B_MOD  = 1;
const uint32_t LEFT_ENCODER_B_CHAN = 1;



const uint8_t  RIGHT_ENCODER_A_MOD  = 1;
const uint32_t RIGHT_ENCODER_A_CHAN = 2;

const uint8_t  RIGHT_ENCODER_B_MOD  = 1;
const uint32_t RIGHT_ENCODER_B_CHAN = 2;

//Ultrasonic
const uint8_t ULTRASONIC_MODULE = 1; //FILLER
const uint32_t ULTRASONIC_CHANNEL = 1; //FILLER

#endif
