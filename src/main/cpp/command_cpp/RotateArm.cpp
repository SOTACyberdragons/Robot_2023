#include "command_headers/RotateArm.h"


void cb::RotateArm::Initialize() {
    AddRequirements(&g_arm);

    g_arm.moveLimb(autoArmVoltage * m_direction);
}

bool cb::RotateArm::IsFinished() {
    double currentSetpoint = g_arm.getSensorPos();

    return (currentSetpoint >= m_setpoint - m_deadBand && 
            currentSetpoint <= m_setpoint + m_deadBand);
}

cb::RotateArm::RotateArm(double setpoint, double deadBand)
    : m_setpoint(setpoint), m_deadBand(deadBand)
{
    if (g_arm.getSensorPos() > m_setpoint) {
        m_direction = 1;
    } else {
        m_direction = -1;
    }
}