#include "command_headers/TurnRobot.h"

cb::TurnRobot::TurnRobot(double degree) 
    : m_degree(degree) 
{}

void cb::TurnRobot::Initialize() {
    std::cout << "Running turn command\n";
    m_initialDegree = g_drivetrain.getGyro().GetYaw();
}

void cb::TurnRobot::Execute() {
    g_drivetrain.tankDriveVolts(-turnRobotVolts, turnRobotVolts);
}

bool cb::TurnRobot::IsFinished() {
    double currentDegree = g_drivetrain.getGyro().GetYaw();

    if (m_degree >= 0) {
        return (currentDegree - m_initialDegree >= m_degree);
    } else {
        return (currentDegree - m_initialDegree <= m_degree);
    }
}