#ifndef ROBOT_CONTAINER
#define ROBOT_CONTAINER

#include <frc2/command/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/XboxController.h>

#include "Constants.h"

//subsystems
#include "subsystem_headers/Drivetrain.h"
#include "subsystem_headers/Climber.h"
#include "subsystem_headers/VisionProcessor.h"

namespace cb {
    //subsystem objects
    inline Drivetrain g_drivetrain;
    inline Climber g_climber;
    inline VisionProcessor m_visionProcessor;

    //the physical xbox controller, mapped to port 0
    static const frc::XboxController controller { 0 };

    // Return XBox left stick for throttle control
    inline double getXBoxThrottle() {
        return controller.GetLeftY() * kMaxDriveSpeed;
    }

    // Return XBox right stick for rotational control
    inline double getXBoxRotation() {
        return controller.GetRightX() * kMaxTurnSpeed;
    }

    static frc::SendableChooser<frc2::Command*> autoChooser;

    [[nodiscard]] frc2::Command* getAuto();

    void configureButtonBindings();

    void addAutoModeOptions();
}

#endif