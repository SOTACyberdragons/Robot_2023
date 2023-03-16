#include "command_headers/MoveArmToIntake.h"

void cb::MoveArmToIntake::Initialize() {
    AddRequirements(&g_arm);
    usingFeedForward = false;

    std::cout << "Running move arm to intake command\n";

    //g_arm.moveLimb(-autoArmVoltage);
}

void cb::MoveArmToIntake::Execute() {
    //std::cout << "Executing\n";
    g_arm.moveLimb(-autoArmVoltage);
}

bool cb::MoveArmToIntake::IsFinished() {
    double sensorPos = g_arm.getSensorPos();
    return (sensorPos >= m_setpoint - 1000 && 
            sensorPos <= m_setpoint + 1000);
}

void cb::MoveArmToIntake::End(bool) {
    std::cout << "Ending Arm to Intake Command\n";
}

cb::MoveArmToIntake::MoveArmToIntake(ArmPosition pos) {
    if (pos == ArmPosition::CONE_POS) {
        m_setpoint = armIntakeConeSetpoint;
    } else {
        m_setpoint = armIntakeCubeSetpoint;
    }
}