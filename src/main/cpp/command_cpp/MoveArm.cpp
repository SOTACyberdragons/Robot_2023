#include "command_headers/MoveArm.h"

void cb::MoveArm::Initialize() {
    AddRequirements(&g_arm);
}

void cb::MoveArm::Execute() {
    g_arm.moveLimb(autoArmVoltage);
}

bool cb::MoveArm::IsFinished() {
    return g_arm.getSensorPos() >= 0;
}

