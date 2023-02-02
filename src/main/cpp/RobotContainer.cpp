#include "RobotContainer.h"

void cb::addAutoModeOptions() {
    autoChooser.AddOption("Forward 5 meter drive", std::make_unique<DriveForward>(g_drivetrain, 5_m));
    autoChooser.AddOption("Backward 5 meter drive", std::make_unique<DriveForward>(g_drivetrain, -5_m));

    frc::SmartDashboard::PutData("Autonomous Modes", &autoChooser);
}

frc2::Command* cb::getSelectedAutoCommand() {
     return autoChooser.GetSelected();
}

void cb::configureButtonBindings() {
    
}

