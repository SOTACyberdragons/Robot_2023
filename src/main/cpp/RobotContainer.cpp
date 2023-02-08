#include "RobotContainer.h"

void cb::addAutoModeOptions() {
    autoChooser.AddOption("5 meter forward path", driveMeters(5_m));
    
    frc::SmartDashboard::PutData("Autonomous Modes", &autoChooser);
}

frc2::Command* cb::getSelectedAutoCommand() {
     return autoChooser.GetSelected();
}

void cb::configureButtonBindings() {
    con2.A().OnTrue(new frc2::InstantCommand([&]() { 
        
    }));
}

