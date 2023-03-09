#include "RobotContainer.h"
#include <functional>

void cb::addAutoModeOptions() {
    autoChooser.AddOption("Test", 
        new frc2::SequentialCommandGroup(
           ramseteCommand(loadPath(PathName::TEST, 0.3_mps, 0.3_mps_sq)), Climb(), StayBalanced()
        )
    );
    autoChooser.AddOption("Blue1_Left_Charge", 
        new frc2::SequentialCommandGroup(
            ramseteCommand(loadPath(PathName::BLUE1_LEFT_CHARGE, 0.3_mps, 0.3_mps_sq)), Climb(), StayBalanced()
        )
    );

    autoChooser.AddOption("Climb", 
        new frc2::SequentialCommandGroup(Climb(), StayBalanced()));

    autoChooser.AddOption("Stay Balanced", new StayBalanced());
    
    frc::SmartDashboard::PutData("Autonomous Modes", &autoChooser);
}

frc2::Command* cb::getSelectedAutoCommand() {
    return autoChooser.GetSelected();
}

void cb::configureButtonBindings() {
    con1.RightTrigger().OnTrue(new frc2::InstantCommand([]() {
        g_frontIntake.spinWheels(frontIntakeWheelPower);
    }));
    con1.RightTrigger().OnFalse(new frc2::InstantCommand([]() {
        g_frontIntake.spinWheels(0);
    }));
    con1.LeftTrigger().OnTrue(new frc2::InstantCommand([]() {
        g_frontIntake.spinWheels(-frontIntakeWheelPower);
    }));
    con1.LeftTrigger().OnFalse(new frc2::InstantCommand([]() {
        g_frontIntake.spinWheels(0);
    }));
    
    con1.X().OnTrue(new frc2::InstantCommand([]() {
        g_frontIntake.changeDirection(0.1);
    }));
    con1.X().OnFalse(new frc2::InstantCommand([]() {
        g_frontIntake.changeDirection(0);
    }));

    con1.B().OnTrue(new frc2::InstantCommand([]() {
        g_frontIntake.changeDirection(-0.1);
    }));
    con1.B().OnFalse(new frc2::InstantCommand([]() {
        g_frontIntake.changeDirection(0);
    }));

    con1.Y().OnTrue(new frc2::InstantCommand([]() {
        std::cout << g_frontIntake.getFXSensorPos() << std::endl;
    }));

    con1.RightBumper().OnTrue(new ToggleFrontIntake());
    
    con2.LeftBumper().OnTrue(new frc2::InstantCommand([]() {
        g_arm.resetPosition();
        std::cout << "New position: " << g_arm.getSensorPos() << std::endl;
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
                g_arm.moveLimb(con2.GetLeftY());
            },
            [](bool) {},
            []() { return false; }
        )
    );
    
    frc2::CommandScheduler::GetInstance().Schedule(
        new frc2::FunctionalCommand(
            []() {},
            []() {
                g_armIntake.grab(con2.GetRightY() * maxArmIntakePower);
            },
            [](bool) {},
            []() { return false; }
        )
    );
    //input for driving the robot
    frc2::CommandScheduler::GetInstance().Schedule(new frc2::FunctionalCommand(
        [&]() {}, //no initialization needs
        [&]() { //execution function
            g_drivetrain.arcadeDrive(getXBoxThrottle(), -getXBoxRotation()); 
        },
        [](bool) {}, //never ends
        []() { return false; }, //never ends
        { &g_drivetrain } 
    ));
}