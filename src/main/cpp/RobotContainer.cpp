#include "RobotContainer.h"
#include <string>

void cb::addAutoModeOptions() {
    autoChooser.AddOption("5 meter forward path", new frc2::RamseteCommand(driveMeters(5_m)));
    
    frc::SmartDashboard::PutData("Autonomous Modes", &autoChooser);
}

frc2::Command* cb::getSelectedAutoCommand() {
     return autoChooser.GetSelected();
}

void cb::configureButtonBindings() {
    con2.A().OnTrue(new frc2::InstantCommand([&]() { //rotate the arm back
        g_arm.moveLimb(armVoltage);
    }));
    con2.B().OnTrue(new frc2::InstantCommand([&]() { //rotate the arm forward
        g_arm.moveLimb(-armVoltage);
    }));
    con2.X().OnTrue(new frc2::InstantCommand([&]() { //turn the solenoid 10 degrees
        g_arm.activateSolenoid(true);
    }));
    con2.Y().OnTrue(new frc2::InstantCommand([&]() { //turn the solenoid 20 degrees
        g_arm.activateSolenoid(false);
    }));

    //input for driving the robot
    frc2::CommandScheduler::GetInstance().Schedule(new frc2::FunctionalCommand(
        [&]() {}, //no initialization needs
        [&]() { //execution function
            g_drivetrain.arcadeDrive(getXBoxThrottle(), getXBoxRotation()); 
        },
        [&](bool) {}, //never ends
        [&]() { return false; }, //never ends
        {} 
    ));
}