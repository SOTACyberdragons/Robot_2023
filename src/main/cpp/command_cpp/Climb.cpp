#include "command_headers/Climb.h"

void cb::Climb::Initialize() {
    AddRequirements(&g_drivetrain);
    m_lastRoll = g_drivetrain.getGyro().GetRoll();
    m_startTime = high_resolution_clock::now();
}

void cb::Climb::Execute() {
    m_deltaRoll = g_drivetrain.getGyro().GetRoll() - m_lastRoll;
    m_lastRoll = g_drivetrain.getGyro().GetRoll();

    g_drivetrain.tankDriveVolts(-rampVoltage, -rampVoltage);
}

bool cb::Climb::IsFinished() {
    return (m_deltaRoll > 0.41 && high_resolution_clock::now() - m_startTime > 0.3s);
}
