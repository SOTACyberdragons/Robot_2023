#include "command_headers/Climb.h"

void cb::Climb::Initialize() {
    AddRequirements(&g_drivetrain);
    m_lastRoll = g_drivetrain.getGyro().GetRoll();
    m_rampTime = high_resolution_clock::now();
    m_voltage = toRampVoltage;
    m_onRamp = false;
    m_isFinished = false;
}

void cb::Climb::Execute() {
    m_deltaRoll = g_drivetrain.getGyro().GetRoll() - m_lastRoll;
    m_lastRoll = g_drivetrain.getGyro().GetRoll();

    using namespace std::chrono_literals;

    if (m_deltaRoll > 0.3 && !m_onRamp) {
        m_onRamp = true;
        m_voltage = onRampVoltage;
        m_rampTime = high_resolution_clock::now();
    } else if (m_deltaRoll > 0.3 && m_onRamp && high_resolution_clock::now() - m_rampTime > 1.3s) {
        m_isFinished = true;
        return;
    }

    g_drivetrain.tankDriveVolts(-m_voltage, -m_voltage);
}

bool cb::Climb::IsFinished() {
    return m_isFinished;
}
