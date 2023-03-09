#include "command_headers/ToggleFrontIntake.h"

void cb::ToggleFrontIntake::Initialize() {
    AddRequirements(&g_frontIntake);
    g_frontIntake.setFXSensorPosition(m_setpoint); //update intake fx position with previous endpoint

    if (m_up) {
        m_direction = -1;
        m_setpoint = frontIntakeDownPos;
    } else {
        m_direction = 1;
        m_setpoint = frontIntakeUpPos;
    }
}

void cb::ToggleFrontIntake::Execute() {
    g_frontIntake.changeDirection(frontIntakeDirPower * m_direction);
}

bool cb::ToggleFrontIntake::IsFinished() {
    return (g_frontIntake.getFXSensorPos() <= m_setpoint + 500 &&
            g_frontIntake.getFXSensorPos() >= m_setpoint - 500);
}

void cb::ToggleFrontIntake::End(bool) {
    m_up = !m_up;
    g_frontIntake.changeDirection(0);
}