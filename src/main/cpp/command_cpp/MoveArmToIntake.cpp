#include "command_headers/MoveArmToIntake.h"

void cb::MoveArmToIntake::Initialize() {
    usingFeedForward = false;
    if (IsFinished()) {
        Cancel();
    }
}

void cb::MoveArmToIntake::Execute() {
    g_arm.moveLimb(-autoArmVoltage);
}

bool cb::MoveArmToIntake::IsFinished() {
    return (g_arm.getSensorPos() >= m_setpoint - 1000 && 
            g_arm.getSensorPos() <= m_setpoint + 1000);
}

cb::MoveArmToIntake::MoveArmToIntake(ArmPosition pos) {
    if (pos == ArmPosition::CONE_POS) {
        m_setpoint = armIntakeConeSetpoint;
    } else {
        m_setpoint = armIntakeCubeSetpoint;
    }
}