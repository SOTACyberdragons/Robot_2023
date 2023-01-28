#include "command_headers/DifferentialDriveWithJoysticks.h"

void cb::DifferentialDriveWithJoysticks::Execute() {
    double forwardSpeed = getXBoxThrottle();
    double rotationSpeed = getXBoxRotation();

    g_drivetrain.arcadeDrive(forwardSpeed, rotationSpeed);
}

cb::DifferentialDriveWithJoysticks::DifferentialDriveWithJoysticks() {
    AddRequirements(&g_drivetrain);
}