#include "RobotContainer.h"

void cb::addAutoModeOptions() {
    autoChooser.AddOption("Climb", new Climb());
    frc::SmartDashboard::PutData("Autonomous Modes", &autoChooser);
}

frc2::Command* cb::getSelectedAutoCommand() {
    return autoChooser.GetSelected();
}

void cb::configureButtonBindings() {
    con1.RightTrigger().OnTrue(new frc2::InstantCommand([]() {
        std::cout << "Pitch: " << g_drivetrain.getGyro().GetPitch() << std::endl;
        std::cout << "Roll: " << g_drivetrain.getGyro().GetRoll() << std::endl;
        std::cout << "Yaw: " << g_drivetrain.getGyro().GetYaw() << std::endl;
        std::cout << "Low Power Mode: " << lowPower << std::endl;
    }));

    con1.A().OnTrue(new frc2::InstantCommand(
        []() {
            lowPower = !lowPower; //toggle low power mode for drivetrain motors
            if (lowPower) {
                kMaxDriveSpeed = 0.5;
                kMaxTurnSpeed = 0.5;
            } else {
                kMaxDriveSpeed = 0.85;
                kMaxTurnSpeed = 0.85;
            }
        }
    ));

    frc2::CommandScheduler::GetInstance().Schedule(
        new frc2::FunctionalCommand(
            []() {},
            [&]() {
                double leftY = con1.GetLeftY();
                double feedForward = sin(leftY);
                g_arm.moveLimb(units::volt_t((leftY * maxArmVoltage) + (feedForward * maxFeedForward)));
            },
            [](bool) {},
            []() { return false; }
        )
    );
    //input for driving the robot
    // frc2::CommandScheduler::GetInstance().Schedule(new frc2::FunctionalCommand(
    //     [&]() {}, //no initialization needs
    //     [&]() { //execution function
    //         g_drivetrain.arcadeDrive(getXBoxThrottle(), -getXBoxRotation()); 
    //     },
    //     [&](bool) {}, //never ends
    //     [&]() { return false; }, //never ends
    //     { &g_drivetrain } 
    // ));
}