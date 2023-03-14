#include "RobotContainer.h"
#include <functional>

void cb::addAutoModeOptions() {
    autoChooser.AddOption("Test", 
        new frc2::SequentialCommandGroup(
           ramseteCommand(loadPath(PathName::TEST, 0.3_mps, 0.3_mps_sq)), Climb(1.28_m), StayBalanced()
        )
    );
    autoChooser.AddOption("Blue1_Left_Charge", 
        new frc2::SequentialCommandGroup(
            ramseteCommand(loadPath(PathName::BLUE1_LEFT_CHARGE, 0.3_mps, 0.3_mps_sq)), Climb(1.28_m), StayBalanced()
        )
    );

    autoChooser.AddOption("Climb and Stay Balanced", 
        new frc2::SequentialCommandGroup(Climb(1.17_m), Wait(50ms), StayBalanced()));
    autoChooser.AddOption("Pure Climb", new Climb(1.17_m));

    autoChooser.AddOption("Stay Balanced", new StayBalanced());
    
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
    
    driverCon.X().OnTrue(new frc2::InstantCommand([]() {
        g_frontIntake.toggleJaws();
    }));
    
    driverCon.LeftBumper().OnTrue(new ToggleFrontIntake(false));

    armCon.LeftBumper().OnTrue(new frc2::InstantCommand(
        [&]() {
            if (g_frontIntake.isClosed()) {
                coneHandoff.Schedule();
            } else {
                cubeHandoff.Schedule();
            }
        }
    ));

    armCon.B().OnTrue(new frc2::InstantCommand([]() {
        g_arm.toggleArmBase();
    }));

    armCon.Y().OnTrue(new frc2::InstantCommand([]() {
        if (cubeHandoff.IsScheduled()) {
            cubeHandoff.Cancel();
        }
        if (coneHandoff.IsScheduled()) {
            coneHandoff.Cancel();
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

    frc2::CommandScheduler::GetInstance().Schedule(
        new frc2::FunctionalCommand(
            []() {},
            [&]() {
                g_arm.moveLimb(armCon.GetLeftY());
            },
            [](bool) {},
            []() { return false; }
        )
    );
    
    frc2::CommandScheduler::GetInstance().Schedule(
        new frc2::FunctionalCommand(
            []() {},
            []() {
                g_armIntake.grab(armCon.GetRightY() * maxArmIntakePower);
            },
            [](bool) {},
            []() { return false; }
        )
    );
    //input for driving the robot
    frc2::CommandScheduler::GetInstance().Schedule(new frc2::FunctionalCommand(
        [&]() {}, //no initialization needs
        [&]() { //execution function
            g_drivetrain.arcadeDrive(getXBoxThrottle(), getXBoxRotation()); 
        },
        [](bool) {}, //never ends
        []() { return false; }, //never ends
        { &g_drivetrain } 
    ));
}