#include "RobotContainer.h"

void cb::addAutoModeOptions() {
    autoChooser.AddOption("Normal Climb", new Climb(1.17_m));
    autoChooser.AddOption("WinClimb", new WinClimb(1.17_m));
    frc::SmartDashboard::PutData("Autonomous Modes", &autoChooser);
}

frc2::Command* cb::getSelectedAutoCommand() {
    return autoChooser.GetSelected();
}

void cb::configureButtonBindings() {
    //front intake spin commands
    driverCon.RightTrigger().OnTrue(&spinFrontIntakeForward);
    driverCon.RightTrigger().OnFalse(&stopSpinningFrontIntake);
    driverCon.LeftTrigger().OnTrue(&spinFrontIntakeBack);
    driverCon.LeftTrigger().OnFalse(&stopSpinningFrontIntake);

    //smartdashboard climb testing
    driverCon.B().OnTrue(&testWinClimb);
    driverCon.Y().OnTrue(&testClimb);

    driverCon.A().OnTrue(&toggleLowPowerMode); //lower power mode toggling

    driverCon.X().OnTrue(&toggleJaws); //open and close front intake
    
    driverCon.LeftBumper().OnTrue(&driverToggleIntake);

    frc2::CommandScheduler::GetInstance().Schedule(&driveInput); //input for driving the robot

    armCon.LeftBumper().OnTrue(&cubeHandoff);

    armCon.B().OnTrue(&toggleArmBase);

    armCon.A().OnTrue(&startHandoff);
    armCon.Y().OnTrue(&cancelHandoff);

    frc2::CommandScheduler::GetInstance().Schedule(&armInput);
    frc2::CommandScheduler::GetInstance().Schedule(&armIntakeInput);
}