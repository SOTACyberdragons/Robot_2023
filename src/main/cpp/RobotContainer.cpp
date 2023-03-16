#include "RobotContainer.h"

void cb::addAutoModeOptions() {
    autoChooser.AddOption("Pure Climb", new Climb(1.17_m));
    
    frc::SmartDashboard::PutData("Autonomous Modes", &autoChooser);
}

frc2::Command* cb::getSelectedAutoCommand() {
    return autoChooser.GetSelected();
}

void cb::configureButtonBindings() {
    driverCon.RightTrigger().OnTrue(&spinFrontIntakeForward);
    driverCon.RightTrigger().OnFalse(&stopSpinningFrontIntake);
    driverCon.LeftTrigger().OnTrue(&spinFrontIntakeBack);
    driverCon.LeftTrigger().OnFalse(&stopSpinningFrontIntake);

    driverCon.RightBumper().OnTrue(&testClimb);
    
    driverCon.X().OnTrue(&toggleJaws);
    
    driverCon.LeftBumper().OnTrue(&driverToggleIntake);

    armCon.LeftBumper().OnTrue(&cubeHandoff);

    armCon.B().OnTrue(&toggleArmBase);

    armCon.A().OnTrue(&startHandoff);
    armCon.Y().OnTrue(&cancelHandoff);

    // armCon.RightTrigger().OnTrue(new frc2::InstantCommand([]() {
    //     usingFeedForward = !usingFeedForward;
    // }));

    driverCon.A().OnTrue(&toggleLowPowerMode);

    // frc2::CommandScheduler::GetInstance().Schedule(
    //     new frc2::FunctionalCommand(
    //         []() {},
    //         [&]() {
    //             g_arm.moveLimb(armCon.GetLeftY());
    //         },
    //         [](bool) {},
    //         []() { return false; }
    //     )
    // );

    //frc2::CommandScheduler::GetInstance().Schedule(&armInput);
    
    // frc2::CommandScheduler::GetInstance().Schedule(new frc2::FunctionalCommand(
    //         []() {},
    //         []() {
    //             //g_armIntake.grab(armCon.GetRightY() * maxArmIntakePower);
    //         },
    //         [](bool) {},
    //         []() { return false; }
    //     )
    // );
    frc2::CommandScheduler::GetInstance().Schedule(&armInput);
    frc2::CommandScheduler::GetInstance().Schedule(&armIntakeInput);

    frc2::CommandScheduler::GetInstance().Schedule(&driveInput);
    //input for driving the robot
    //driveInput.Schedule();
}