#include "command_headers/Climb.h"

void cb::Climb::Initialize() {
    AddRequirements(&g_drivetrain);
}

void cb::Climb::Execute() {
    auto pose = g_drivetrain.getPose();

    if (std::abs(std::atan(pose.Rotation().Radians().to<double>())) > 0.15) { //if robot is tilted back
        m_onTop = false;
        g_drivetrain.tankDriveVolts(rampVoltage, rampVoltage);
    } else {
        if (!m_onTop) { //if the robot just got to the top of the community zone
            m_startTime = system_clock::now();
            m_onTop = true;
        } 
        //if it has been 3 seconds, stop climbing
        if (std::chrono::duration_cast<std::chrono::seconds>(system_clock::now() - m_startTime) > 
           std::chrono::seconds(3)) 
        { 
            m_finished = true;
        } else { //otherwise, send top power to motor
            g_drivetrain.tankDriveVolts(topVoltage, topVoltage);
        }
    }
}

bool cb::Climb::IsFinished() {
    return m_finished;
}