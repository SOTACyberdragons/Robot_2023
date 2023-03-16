#include "RobotContainer.h"

void cb::addAutoModeOptions() {
    autoChooser.AddOption("Pure Climb", new Climb(1.17_m));
    
    frc::SmartDashboard::PutData("Autonomous Modes", &autoChooser);
}

frc2::Command* cb::getSelectedAutoCommand() {
    return autoChooser.GetSelected();
}

void cb::configureButtonBindings() {
    driverCon.RightTrigger().OnTrue(new frc2::InstantCommand([]() {
        g_frontIntake.spinWheels(frontIntakePower);
    }));
    driverCon.RightTrigger().OnFalse(new frc2::InstantCommand([]() {
        g_frontIntake.spinWheels(0);
    }));
    driverCon.LeftTrigger().OnTrue(new frc2::InstantCommand([]() {
        g_frontIntake.spinWheels(-frontOuttakePower);
    }));
    driverCon.LeftTrigger().OnFalse(new frc2::InstantCommand([]() {
        g_frontIntake.spinWheels(0);
    }));

    driverCon.RightBumper().OnTrue(
        new frc2::InstantCommand([]() {
            climbCommand.setGoal(units::meter_t(frc::SmartDashboard::GetNumber("Climbing Distance", 1.17)));
            climbCommand.Schedule();
        })
    );
    
    driverCon.X().OnTrue(new frc2::InstantCommand([]() {
        g_frontIntake.toggleJaws();
    }));
    
    driverCon.LeftBumper().OnTrue(new ToggleFrontIntake(false));

    driverCon.Y().OnTrue(new frc2::InstantCommand([]() {
        climbCommand.Cancel();
        climbCommand.Schedule();
    }));

    armCon.LeftBumper().OnTrue(&cubeHandoff);

    armCon.B().OnTrue(new frc2::InstantCommand([]() {
        g_arm.toggleArmBase();
    }));

    armCon.Y().OnTrue(new frc2::InstantCommand([]() {
        if (cubeHandoff.IsScheduled()) {
            cubeHandoff.Cancel();
        }
    }));

    armCon.RightTrigger().OnTrue(new frc2::InstantCommand([]() {
        usingFeedForward = !usingFeedForward;
    }));

    driverCon.A().OnTrue(new frc2::InstantCommand( 
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