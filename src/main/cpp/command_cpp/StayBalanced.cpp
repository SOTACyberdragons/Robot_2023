#include "command_headers/StayBalanced.h"

void cb::StayBalanced::Initialize() {
    m_startTime = high_resolution_clock::now();
}

void cb::StayBalanced::Execute() {
    auto speed = g_drivetrain.getWheelSpeeds().right;
    if (speed < 0_mps) {
        g_drivetrain.tankDriveVolts(1_V, 1_V);
    } else if (speed > 0_mps) {
        g_drivetrain.tankDriveVolts(-1_V, -1_V);
    }
}

bool cb::StayBalanced::IsFinished() {
    return false;
}