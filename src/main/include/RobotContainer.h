#ifndef ROBOT_CONTAINER
#define ROBOT_CONTAINER

#include <memory>

#include <frc2/command/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/XboxController.h>

#include "Constants.h"

//subsystems
#include "subsystem_headers/Drivetrain.h"
#include "subsystem_headers/VisionProcessor.h"

//auto commands
#include "command_headers/auto/DriveForward.h"

namespace cb {
    //inline VisionProcessor m_visionProcessor;

    //the physical xbox controller, mapped to port 0
    static const frc::XboxController controller { 0 };

    // Return XBox left stick for throttle control
    inline double getXBoxThrottle() {
        return -1 * controller.GetLeftY() * kMaxDriveSpeed;
    }

    // Return XBox right stick for rotational control
    inline double getXBoxRotation() {
        return controller.GetRightX() * kMaxTurnSpeed;
    }

    static frc::SendableChooser<std::unique_ptr<frc2::Command>> autoChooser;

    void configureButtonBindings();

    void addAutoModeOptions();
    frc2::Command* getSelectedAutoCommand();
}

#endif