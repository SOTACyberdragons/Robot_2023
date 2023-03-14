#include "command_headers/StayBalanced.h"

void cb::StayBalanced::Initialize()
{
    
}

void cb::StayBalanced::Execute()
{
    double currentRoll = g_drivetrain.getGyro().GetRoll();

    units::volt_t volts = toRampVoltage;

    if (currentRoll < -2) {
        g_drivetrain.tankDriveVolts(-volts, -volts);
    } else if (currentRoll > 2) {
        g_drivetrain.tankDriveVolts(volts, volts);
    } else {
        g_drivetrain.setMotorMode(NeutralMode::Brake);
        m_finished = true;
    }
}

bool cb::StayBalanced::IsFinished()
{
    return m_finished;
}