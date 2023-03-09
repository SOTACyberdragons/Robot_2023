#include "command_headers/MoveArm.h"

void cb::MoveArm::Initialize() {
    AddRequirements(&g_arm);
    //send positive voltage to move arm from back exterior
    if (g_arm.getSensorPos() > m_setpoint) {
        m_direction = 1;
    } else {
        m_direction = -1;
    }
}

void cb::MoveArm::Execute() {
    g_arm.moveLimb(autoArmVoltage * m_direction);
}

bool cb::MoveArm::IsFinished() {
    return (g_arm.getSensorPos() >= m_setpoint + 5000 && 
            g_arm.getSensorPos() <= m_setpoint + 5000);
}

cb::MoveArm::MoveArm(double setpoint) 
    : m_setpoint(setpoint) 
{}
