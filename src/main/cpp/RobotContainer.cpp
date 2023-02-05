#include "RobotContainer.h"

void cb::addAutoModeOptions() {
    autoChooser.AddOption("S path", cb::driveClimb());
    
    frc::SmartDashboard::PutData("Autonomous Modes", &autoChooser);
}

frc2::Command* cb::getSelectedAutoCommand() {
     return autoChooser.GetSelected();
}

void cb::configureButtonBindings() {
    
}

