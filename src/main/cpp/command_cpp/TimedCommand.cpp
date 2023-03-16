#include "command_headers/TimedCommand.h"

void cb::TimedCommand::Initialize() {
    if (m_base != nullptr) {
        AddRequirements(m_base);
    }

    m_startTime = high_resolution_clock::now();
    std::cout << "Running\n";
    m_initialize();
}

void cb::TimedCommand::Execute() {
    m_execute();
}

void cb::TimedCommand::End(bool) {
    m_end();
}

bool cb::TimedCommand::IsFinished() {
    return high_resolution_clock::now() - m_startTime >= m_time;
}

cb::TimedCommand::TimedCommand(frc2::Subsystem* base, 
                               std::function<void()> initialize, 
                               std::function<void()> execute,
                               std::function<void()> end, 
                               milliseconds time)
    : m_base(base), m_initialize(initialize), m_execute(execute), m_end(end), m_time(time)
{}