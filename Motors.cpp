#include "Motors.h"
#include "main.h"
#include "612.h"
#include <Relay.h>
Motors::Motors()
{
    FR = new Talon(TALON_FL_MODULE, TALON_FL_CHANNEL); //drivetrain
    FL = new Talon(TALON_RL_MODULE, TALON_RL_CHANNEL);
    RR = new Talon(TALON_FR_MODULE, TALON_FR_CHANNEL);
    RL = new Talon(TALON_RR_MODULE, TALON_RR_CHANNEL);

    drivetrain [0] = FR;
    drivetrain [1] = FL;
    drivetrain [2] = RR;
    drivetrain [3] = RL;
    
    
    grabber = new Talon(GRAB_MOD, GRAB_CHAN);
    
    tilt = new CANJaguar(TILT_DEV);
    
    compressor = new Relay(PNUM_RELAY_MODULE, PNUM_RELAY_CHANNEL);
}

Motors::~Motors()
{
}

void Motors::runMotor(int motor)
{
    static bool print = false;
    static int previousMotor = -1;
    static float previousPower = 0.0;
    power = robot->driverJoy -> GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
    
    if ((previousMotor != motor) || previousPower != power) 
    {
        print = true;
        previousMotor = motor;
        previousPower = power;
    }
    else
    {
        print = false;
    }
    if (motor == 0)
        drive(print); //implementation of RobotDrive
    /*
    else if (motor == 1)
        setTalon(FR,print,motor);
    else if (motor == 2)
        setTalon(FL,print,motor);
    else if (motor == 3)
        setTalon(RR,print,motor);
    else if (motor == 4)
        setTalon(RL,print,motor);
    */
    
    
    else if (motor >= 1 && motor <=4)
        setTalon(motor,print);
                 
    
    else if (motor == 5)
        setTalon(grabber,print,motor);

    else if (motor == 6) //Compressor NEVER SET TO REVERSE
    {
        static bool warned = false;
        static Relay::Value compressorDirection = Relay::kReverse;
        if (robot->driverJoy->GetRawButton(BUTTON_START) && ((power > JOYSTICK_ZERO_TOLERANCE) || (power < JOYSTICK_ZERO_TOLERANCE*-1)))
        {
            compressor->Set(Relay::kForward);
            if (compressorDirection != Relay::kForward)
            {
                if (!warned)
                {
                    std::printf("RELAY OVERRIDE: WILL NOT TURN OFF AUTOMATICALLY");
                    warned = true;
                }
                std::printf("Compressor: kForward");
                compressorDirection = Relay::kForward;
            }
        }
        else if ((robot->driverJoy -> IsAxisZero(DRIVER_LEFT_DRIVE_AXIS) == false) && (robot->sense->pnumSwitch->Get() == 0))
        {
            compressor->Set(Relay::kForward);
            if (compressorDirection != Relay::kForward)
            {
                std::printf("Compressor: kForward\n");
                compressorDirection = Relay::kForward;
            }
        }
        else 
        {
            warned = false;
            compressor->Set(Relay::kOff);
            if (compressorDirection != Relay::kOff)
            {
                std::printf("Compressor: kOff\n");
                compressorDirection = Relay::kOff;
            }
        }
    }
    else if (motor == 7) //tilt JAG
    {
        tilt -> Set(power);
        if (print)
            std::printf("6: Jag Tilt: %f\n", power);
    }
    else if (motor >= 8)
    {
        std::printf("MAX\n");
        robot->selection = 70;
    }
}
void Motors::drive(bool print)
{
    left = robot->driverJoy->GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
    right = robot->driverJoy->GetRawAxis(DRIVER_RIGHT_DRIVE_AXIS);
    
    FL -> Set(left);
    RL -> Set(left);
    
    FR -> Set(right);
    RR -> Set(right);
    if (print)
        std::printf("Drivetrain: %f\n", power);
}
void Motors::drive2(bool print)
{
    //TODO I want to test this first, not sure if it will work
    left = robot->driverJoy->GetRawAxis(DRIVER_LEFT_DRIVE_AXIS);
    right = robot->driverJoy->GetRawAxis(DRIVER_RIGHT_DRIVE_AXIS);

    for (int i=0;i<4;i++)
        drivetrain[i] ->Set(power);

    if (print)
        std::printf("Drivetrain Power: %f\n", power);

}
void Motors::disable()
{
    FL->Set(0.0);
    FR->Set(0.0);
    RR->Set(0.0);
    RL->Set(0.0);
    
    grabber->Set(0.0);
    
    tilt->Set(0.0);
    
    compressor->Set(Relay::kOff);
}
void Motors::setTalon(Talon* t, bool print, int motor)
{
    t -> Set(power);
    if (print)
    {
        std::printf("%d: Talon %u : %f\n",motor, 0, power);
    }
}
void Motors::setTalon(int motor, bool print)
{
    drivetrain[motor-1] -> Set(power);
    if (print)
    {
        std::printf("%d: Talon %u : %f\n",motor-1, 0, power); //0 is placeholder
    }
}
