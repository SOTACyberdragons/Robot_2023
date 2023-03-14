#include "command_headers/Wait.h"

void cb::Wait::Initialize() {
    m_startTime = high_resolution_clock::now();
}

bool cb::Wait::IsFinished() {
    return high_resolution_clock::now() - m_startTime >= m_waitTime;
}

cb::Wait::Wait(milliseconds waitTime)
    : m_waitTime(waitTime)
{}