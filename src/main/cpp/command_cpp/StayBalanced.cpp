#include "command_headers/StayBalanced.h"

void cb::StayBalanced::Initialize()
{
    std::cout << "Staying Balanced\n";
    g_drivetrain.setMotorMode(NeutralMode::Coast);
}

void cb::StayBalanced::Execute()
{
    double currentRoll = g_drivetrain.getGyro().GetRoll();

    units::volt_t volts = 1_V;

    if (currentRoll < -2) {
        std::cout << "Going forward\n";
        g_drivetrain.tankDriveVolts(volts, volts);
    } else if (currentRoll > 2) {
        std::cout << "Going back\n";
        g_drivetrain.tankDriveVolts(-volts, -volts);
    } else {
        g_drivetrain.setMotorMode(NeutralMode::Brake);
        m_finished = true;
    }
}

bool cb::StayBalanced::IsFinished()
{
    return m_finished;
}