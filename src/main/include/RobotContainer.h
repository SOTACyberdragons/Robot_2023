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

//subsystems
#include "subsystem_headers/Drivetrain.h"
#include "subsystem_headers/Arm.h"
#include "subsystem_headers/ArmIntake.h"
#include "subsystem_headers/FrontIntake.h"

//auto commands
#include "command_headers/PathplannerPaths.h"
#include "command_headers/RamseteCommandUtil.h"
#include "command_headers/Climb.h"
#include "command_headers/TurnRobot.h"
#include "command_headers/StayBalanced.h"
#include "command_headers/ToggleFrontIntake.h"
#include "command_headers/MoveArmToIntake.h"
#include "command_headers/Wait.h"

//camera stream
#include "CameraCapture.h"

namespace cb {
    //the physical xbox controller, mapped to port 0
    static frc2::CommandXboxController driverCon { 0 }, armCon { 1 };

    static const frc2::Trigger controllerX;

    inline bool lowPower = false; //toggles low/high speed for drivetrain voltage

    inline frc2::SequentialCommandGroup cubeHandoff { 
        ToggleFrontIntake(true), MoveArmToIntake(ArmPosition::CUBE_POS) 
    };
    inline frc2::SequentialCommandGroup coneHandoff { 
        MoveArmToIntake(ArmPosition::CONE_POS), ToggleFrontIntake(true)
    };

    //Return XBox left stick for throttle control
    inline double getXBoxThrottle() {
        return driverCon.GetLeftY() * kMaxDriveSpeed;
    }

    //Return XBox right stick for rotational control
    inline double getXBoxRotation() {
        return driverCon.GetRightX() * kMaxTurnSpeed;
    }

    static frc::SendableChooser<frc2::Command*> autoChooser;

    void configureButtonBindings();

    void addAutoModeOptions();

    [[nodiscard]] frc2::Command* getSelectedAutoCommand();
}

#endif