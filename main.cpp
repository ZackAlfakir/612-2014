#include <cmath>
#include "main.h"
#include "612.h"
#include <DigitalInput.h>
#include <Relay.h>
#include <Joystick.h>
#include "ports.h"
//#include "Netcom.h"
#include "Sensors.h"

main_robot::main_robot()
{
    printf("Hello\n");
    printf("World\n");
}

main_robot::~main_robot()
{
}

void main_robot::RobotInit()
{
    printf("RobotInit entry\n");
    update = new FunctionRegistry();
    driverJoy = new SmoothJoystick(this, DRIVER_JOY_PORT);
    gunnerJoy = new SmoothJoystick(this, GUNNER_JOY_PORT);
    pnum = new Pneumatics(this, PNUM_DIGIN_MODULE, PNUM_DIGIN_CHANNEL, PNUM_RELAY_MODULE, PNUM_RELAY_CHANNEL);
    shift = new Shifter(this, SHIFT_MOD, SHIFT_FCHAN, SHIFT_RCHAN);
    shift->setHigh();
    drive = new DriveTrain(this, TALON_FL_MODULE, TALON_FL_CHANNEL,
                           TALON_RL_MODULE, TALON_RL_CHANNEL,
                           TALON_FR_MODULE, TALON_FR_CHANNEL,
                           TALON_RR_MODULE, TALON_RR_CHANNEL);
    shoot = new Shooter(this, SHOOT_JAG_CAN,
                        SHOOT_TALON_MODULE, SHOOT_TALON_CHANNEL,
                        SHOOT_SLNOID_MODULE, SHOOT_SLNOID_FCHAN, SHOOT_SLNOID_RCHAN,
                        WORM_JAG_CAN,
                        PUNCH_SLNOID_MODULE, PUNCH_SLNOID_FCHAN, PUNCH_SLNOID_RCHAN,
                        SHOOT_ACCEL_MODULE);
    sensors = new Sensors(this, USMODNUMBER, USCHANNEL, ISMODNUMBER, ISCHANNEL, ILMODNUMBER, ILCHANNEL, GYMOD, GYCHAN);
    sensors->setGyroSens(1.0f); //default sensitivity
    printf("Welcome to 612-2014 AERIAL ASSIST\n");
//    netcom = new Netcom();
    autoBot = new Autonomous(this);
}
void main_robot::TeleopInit()
{
    drive->SetSafetyEnabled(true);
    drive->stopAuto();
    shoot->pitchStop();
    shoot->rollerStop();
    shoot->wormStop();
    shift->setHigh();
}
void main_robot::AutonomousInit()
{
    drive->SetSafetyEnabled(false);
    autoBot -> stage = Autonomous::IDLE;
    drive->stopAuto();
    shoot->pitchStop();
    shoot->rollerStop();
    shoot->wormStop();
    shift->setLow();
}
void main_robot::TestInit()
{
//    init_vision();
//    engine -> startContinuous();
}
void main_robot::DisabledInit()
{
    stop_vision();
}

void main_robot::TeleopPeriodic()
{
    update->updateFunctions();
    float left = driverJoy->GetRawAxis(2);
    float right = driverJoy->GetRawAxis(5);
    // up is negative, down is positive
    drive->TankDrive(-left, -right);
/*    static int loopLeft = 0;
    static int loopRight = 0;
    static float prevLeft = 0.0f;
    static float prevRight = 0.0f;

    float rawleft = driverJoy->GetRawAxis(2);
    float rawright = driverJoy->GetRawAxis(5);

    if (fabs(rawleft) < SmoothJoystick::DEADZONE)
    {
        prevLeft = 0.0f;
        loopLeft = 0;
    }
    
    if (loopLeft > 0)
    {
        --loopLeft;
        rawleft = prevLeft;
    }
    
    if (fabs(rawleft - prevLeft) > GLIDE_THRESHOLD)
    {
        rawleft = prevLeft + GLIDE_INCREMENT;
        loopLeft = GLIDE_ITERATIONS;
    }
    
    prevLeft = rawleft;
    
    if (fabs(rawright) < SmoothJoystick::DEADZONE)
    {
        prevRight = 0.0f;
        loopRight = 0;
    }
    
    if (loopRight > 0)
    {
        --loopRight;
        rawright = prevRight;
    }
    
    if (fabs(rawright - prevRight) > GLIDE_THRESHOLD)
    {
        rawright = prevRight + GLIDE_INCREMENT;
        loopRight = GLIDE_ITERATIONS;
    }
    
    prevRight = rawRight;*/
}

void main_robot::AutonomousPeriodic()
{
    shift->shifter->Set(DoubleSolenoid::kReverse);
    update -> updateFunctions();
//    drive -> TankDrive(0.0,0.0);
    drive -> update();
//    autoBot -> updateBasicDrive();
    autoBot -> updateHighGoal();
}

void main_robot::DisabledPeriodic()
{
}
void main_robot::TestPeriodic()
{
    static int output=0;
    if(output%20==0) {
        printf("Supposed to wait: %i\n",autoBot->table->GetBoolean("1/WeWait",false));
    }
    output++;
//    printf("%d", engine->getHotGoal());
//    pnum->checkPressure();
//    pnum->updateSolenoid();
}

void main_robot::init_vision() {
    std::printf("init vision\n");
    engine = new vision();
}

void main_robot::stop_vision() {
    std::printf("stop vision\n");
/*    if(engine!=NULL) {
        if(engine->isContinuousRunning()) {
            engine->stopContinuous();
        }
        delete engine;
        engine=NULL;
    }*/
}

START_ROBOT_CLASS(main_robot)
