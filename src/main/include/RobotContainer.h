#ifndef ROBOT_CONTAINER
#define ROBOT_CONTAINER

#include <memory>
#include <math.h>
#include <iostream>

#include <frc2/command/Command.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/SequentialCommandGroup.h>

#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/FunctionalCommand.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/button/Trigger.h>

#include "Constants.h"

// subsystems
#include "subsystem_headers/Drivetrain.h"
#include "subsystem_headers/Arm.h"
#include "subsystem_headers/ArmIntake.h"
#include "subsystem_headers/FrontIntake.h"

// auto commands
#include "command_headers/PathplannerPaths.h"
#include "command_headers/RamseteCommandUtil.h"
#include "command_headers/Climb.h"
#include "command_headers/TurnRobot.h"
#include "command_headers/StayBalanced.h"
#include "command_headers/ToggleFrontIntake.h"
#include "command_headers/MoveArmToIntake.h"
#include "command_headers/RotateArm.h"
#include "command_headers/Wait.h"
#include "command_headers/TimedCommand.h"

namespace cb
{
    // the physical xbox controller, mapped to port 0
    static frc2::CommandXboxController driverCon{0}, armCon{1};

    inline Climb climbCommand{
        Climb(1.17_m)};

    static const frc2::Trigger controllerX;

    inline bool lowPower = false; // toggles low/high speed for drivetrain voltage

    inline double climbingMeters = 0;

    inline TimedCommand autoOuttake{
        &g_frontIntake, []() {}, []()
        { g_frontIntake.spinWheels(-0.3); },
        []()
        { g_frontIntake.spinWheels(0); },
        1000ms};

    inline frc2::SequentialCommandGroup cubeHandoff{
        ToggleFrontIntake(true), MoveArmToIntake(ArmPosition::CUBE_POS), autoOuttake};

    // Return XBox left stick for throttle control
    inline double getXBoxThrottle()
    {
        return driverCon.GetLeftY() * kMaxDriveSpeed;
    }

    // Return XBox right stick for rotational control
    inline double getXBoxRotation()
    {
        return driverCon.GetRightX() * kMaxTurnSpeed;
    }

    inline frc2::FunctionalCommand driveInput{
        []() {}, // no initialization needs
        []() {   // execution function
            g_drivetrain.arcadeDrive(getXBoxThrottle(), getXBoxRotation());
        },
        [](bool) {}, // never ends
        []()
        { return false; }, // never ends
        {&g_drivetrain}};

    inline frc2::FunctionalCommand armIntakeInput{
        []() {},
        []()
        {
            g_armIntake.grab(armCon.GetRightY() * maxArmIntakePower);
        },
        [](bool) {},
        []()
        { return false; }
    };

    inline frc2::FunctionalCommand armInput
    {
        []() {},
        []()
        {
            g_arm.moveLimb(armCon.GetLeftY());
        },
            [](bool) {},
            []()
        { return false; }
    };

    static frc::SendableChooser<frc2::Command *> autoChooser;

    void configureButtonBindings();

    void addAutoModeOptions();

    [[nodiscard]] frc2::Command *getSelectedAutoCommand();
}

#endif