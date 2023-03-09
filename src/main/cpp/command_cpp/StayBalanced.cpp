#include "command_headers/StayBalanced.h"

void cb::StayBalanced::Initialize()
{
    m_lastTime = high_resolution_clock::now();
}

void cb::StayBalanced::Execute()
{
    if (m_state == State::NONE) {
        auto speed = g_drivetrain.getWheelSpeeds().right;
        if (speed > 0_mps) {
            m_state = State::ADJUSTING_BACK;
        } else if (speed < 0_mps) {
            m_state = State::ADJUSTING_FORWARD;
        }
        m_lastTime = high_resolution_clock::now();
    } else if (m_state == State::ADJUSTING_BACK) {
        if (high_resolution_clock::now() - m_lastTime > 1s) {
            m_state = State::NONE;
        } else {
            g_drivetrain.tankDriveVolts(-1_V, -1_V);
        }
    } else {
        if (high_resolution_clock::now() - m_lastTime > 1s) {
            m_state = State::NONE;
        } else {
            g_drivetrain.tankDriveVolts(1_V, 1_V);
        }
    }
}

bool cb::StayBalanced::IsFinished()
{
    return false;
}