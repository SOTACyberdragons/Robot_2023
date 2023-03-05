#include "command_headers/Climb.h"

void cb::Climb::Initialize() {
    AddRequirements(&g_drivetrain);
    m_lastRoll = g_drivetrain.getGyro().GetRoll();
    m_rampTime = high_resolution_clock::now();
    m_voltage = toRampVoltage;
<<<<<<< HEAD
    m_onRamp = false;
=======
>>>>>>> 658096c3e1fe0d16c25514170a2627d8b61df4f3
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
<<<<<<< HEAD
    } else if (m_deltaRoll > 0.3 && m_onRamp && high_resolution_clock::now() - m_rampTime > 1.8s) {
=======
    } else if (m_deltaRoll > 0.3 && m_onRamp && high_resolution_clock::now() - m_rampTime > 0.3s) {
>>>>>>> 658096c3e1fe0d16c25514170a2627d8b61df4f3
        m_isFinished = true;
        return;
    }

<<<<<<< HEAD
    g_drivetrain.tankDriveVolts(-m_voltage, -m_voltage);
=======
    g_drivetrain.tankDriveVolts(m_voltage, m_voltage);
>>>>>>> 658096c3e1fe0d16c25514170a2627d8b61df4f3
}

bool cb::Climb::IsFinished() {
    return m_isFinished;
}
