#include <Joystick.h>

#include "main.h"
#include "612.h"
#include "SmoothJoystick.h"
#include "ports.h"
#include "Controls.h"


robot_class* robot=NULL;

robot_class::robot_class()
{
}

void robot_class::RobotInit()
{
    robot = this;
    driverJoy = new SmoothJoystick(DRIVER_JOY_PORT);
    
    sense = new Sensors();
    motors = new Motors();
    pneumatics = new Pneumatics();
}

void robot_class::DisabledInit()
{
}

void robot_class::DisabledPeriodic()
{
}

void robot_class::AutonomousInit()
{

}

void robot_class::AutonomousPeriodic()
{

}

void robot_class::TeleopInit()
{

}

void robot_class::TeleopPeriodic()
{

}

void robot_class::TestInit()
{
    button = MOTORS;
    selection = 0;
}

void robot_class::TestPeriodic()
{
    static int lastSelection = 0;
    updateRegistry.update();
    if (selection < 0)
        selection = 0;
    if (selection < lastSelection)
        std::printf("DECREMENT");
    else if (selection > lastSelection)
        std::printf("INCREMENT");
    getButtons();
    if (button == SENSORS)
        sense -> runSensors(selection);
    else if (button == PNEUMATICS)
        pneumatics -> runPneumatics(selection);
    else if (button == MOTORS)
        motors -> runMotor(selection);
    lastSelection = selection;
}
void robot_class::printStuff()
{
    std::printf("R1: Increment selection\nL1: Decrement selection\nLeft Analog stick for control\n\n");
    std::printf("TRIANGLE: Print instructions\n");
    std::printf("CIRCLE: Pneumatics\n\t0:Shifters\n\t1:Clamp\n");
    std::printf("SQUARE: Sensors\n\t0: Digital Switch\n\t1: Left Encoder\n\t2:Right Encoder\n");
    std::printf("X: MOTORS\n\t0: Drivetrain\n\t1: Talon 1\n\t2: Talon 2\n\t3: Talon 3\n\t4: Talon 4\n\n\t5: Grabber\n\t6: Tilt control\n\t7: Compressor\n");
}
void robot_class::getButtons()
{
    if (driverJoy->GetRawButton(BUTTON_X))
    {
        button = SENSORS;
        std::printf("SENSORS\n");
        selection = 0;
    }
    if (driverJoy->GetRawButton(BUTTON_A))
    {
        button = MOTORS;
        std::printf("MOTORS\n");
        selection = 0;
    }
    else if (driverJoy->GetRawButton(BUTTON_B))
    {
        button = PNEUMATICS;
        std::printf("PNEUMATICS\n");
        selection = 0;
    }
    else if (driverJoy->GetRawButton(BUTTON_Y))
    {
        printStuff();
    }
    if (driverJoy->GetRawButton(BUTTON_R1))
    {
        selection++;
        //std::printf("INCREMENT\n");
        if (button == MOTORS)
        {
            motors->disable();
        }
    }
    else if (driverJoy->GetRawButton(BUTTON_L1))
    {
        selection--;
        //std::printf("DECREMENT\n");
        if (button == MOTORS)
        {
            motors->disable();
        }
    }
}

START_ROBOT_CLASS(robot_class)
