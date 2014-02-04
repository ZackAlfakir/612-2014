#include "Sensors.h"
#include "ports.h"

#include "main.h"
#include "612.h"

Sensors::Sensors()
{
    pnumSwitch = new DigitalInput(PNUM_DIGIN_MODULE, PNUM_DIGIN_CHANNEL);
    left = new Encoder(LEFT_ENCODER_A_MOD,LEFT_ENCODER_A_CHAN,LEFT_ENCODER_B_MOD,LEFT_ENCODER_B_CHAN);
    right = new Encoder(RIGHT_ENCODER_A_MOD,RIGHT_ENCODER_A_CHAN,RIGHT_ENCODER_B_MOD,RIGHT_ENCODER_B_CHAN);
    ultrasonic = new AnalogChannel(ULTRASONIC_MODULE, ULTRASONIC_CHANNEL);
}
void Sensors::runSensors(int sense)
{
    double prevVal = 0.0;
    if (sense == 0)
    {
        if ((double)pnumSwitch -> Get() != prevVal)
        {
            std::printf("PnumSwitch: %f\n",(double)pnumSwitch -> Get());
            prevVal = (double)pnumSwitch -> Get();
        }
    }
    else if(sense == 1)
    {
        if ((double)left->Get() != prevVal)
        {
            std::printf("Left Encoder: %f\n", (double)left->Get());
            prevVal = (double)left->Get();
        }
    }
    else if (sense == 2)
    {
        if ((double)right->Get() != prevVal)
        {
            std::printf("Right Encoder: %f\n", (double)right->Get());
            prevVal = (double)right->Get();
        }
    }
    else if (sense == 3)
    {
        if ((double)ultrasonic->GetVoltage() != prevVal)
        {
            std::printf("UltraSonic Voltage: %f\nUltraSonic Value: %f\n\n", (double)ultrasonic->GetVoltage(), (double)ultrasonic->GetValue());
            prevVal = (double)ultrasonic->GetValue();
        }
    }
    else if (sense >= 4)
    {
        std::printf("MAX");
        robot->selection = 30;
    }
    prevVal = sense;
}
