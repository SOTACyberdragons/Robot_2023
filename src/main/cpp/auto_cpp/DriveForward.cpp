#include "command_headers/auto/DriveForward.h"

void cb::DriveForward::Initialize() {
    AddRequirements(&m_drive);
}

void cb::DriveForward::Execute() {
    m_drive.arcadeDrive(m_power, 0);
}

bool cb::DriveForward::IsFinished() {
    return m_drive.getRightDistance() > m_meters;
}

cb::DriveForward::DriveForward(Drivetrain& drivetrain, units::meter_t meters) 
    : m_drive(drivetrain), m_meters(meters)
{
    if (m_meters < 0_m) {
        m_power = -0.35;
    } else {
        m_power = 0.35;
    }
}