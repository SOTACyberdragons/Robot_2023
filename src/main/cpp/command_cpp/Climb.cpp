#include "command_headers/Climb.h"

void cb::Climb::Initialize() {
    AddRequirements(&g_drivetrain);
}

void cb::Climb::Execute() {
    g_drivetrain.tankDriveVolts(m_voltage, m_voltage);
}

bool cb::Climb::IsFinished() {
    return false;
}

