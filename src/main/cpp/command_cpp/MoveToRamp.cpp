#include "command_headers/MoveToRamp.h"

using namespace pathplanner;

PathPlannerTrajectory cb::Blue1ToLeftCharge() {
    return PathPlanner::loadPath("Pathplanner/Blue1_Left_Charge.path", PathConstraints(4_mps, 3_mps_sq));
    auto x = PathPlanner::loadPath("Example Path", PathConstraints(4_mps, 3_mps_sq));
}

void cb::MoveToRamp::Initialize() {
    AddRequirements(&g_drivetrain);
    m_lastRoll = g_drivetrain.getGyro().GetRoll();
    m_deltaRoll = 0;
}

void cb::MoveToRamp::Execute() {
    m_deltaRoll = g_drivetrain.getGyro().GetRoll() - m_lastRoll;
    m_lastRoll = g_drivetrain.getGyro().GetRoll();

    g_drivetrain.tankDriveVolts(-groundVoltage, -groundVoltage);
}   

bool cb::MoveToRamp::IsFinished() {
    return m_deltaRoll > 0.7;
}