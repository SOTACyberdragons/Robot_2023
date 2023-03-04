#ifndef ROBOT_CONTAINER
#define ROBOT_CONTAINER

#include <memory>
#include <math.h>

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

//auto commands
#include "command_headers/PathplannerPaths.h"
#include "command_headers/RamseteCommandUtil.h"
#include "command_headers/MoveArm.h"
#include "command_headers/Climb.h"

namespace cb {
    //the physical xbox controller, mapped to port 0
    static frc2::CommandXboxController con1 { 0 }, con2 { 1 };

    static const frc2::Trigger controllerX;

    inline bool lowPower = false; //toggles low/high speed for drivetrain voltage

    //Return XBox left stick for throttle control
    inline double getXBoxThrottle() {
        return con1.GetLeftY() * kMaxDriveSpeed;
    }

    //Return XBox right stick for rotational control
    inline double getXBoxRotation() {
        return con1.GetRightX() * kMaxTurnSpeed;
    }

    static frc::SendableChooser<frc2::Command*> autoChooser;

    void configureButtonBindings();

    void addAutoModeOptions();

    [[nodiscard]] frc2::Command* getSelectedAutoCommand();
}

#endif