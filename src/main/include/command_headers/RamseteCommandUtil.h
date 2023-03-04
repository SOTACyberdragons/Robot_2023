#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/RamseteCommand.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/InstantCommand.h>

#include <frc/geometry/Pose2d.h>

#include <frc/trajectory/TrajectoryConfig.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc/trajectory/constraint/TrajectoryConstraint.h>

#include <frc/controller/RamseteController.h>

#include "subsystem_headers/Drivetrain.h"
#include "Constants.h"

namespace cb {
    frc2::RamseteCommand ramseteCommand(units::meter_t meters);

    frc2::RamseteCommand ramseteCommand(frc::Trajectory trajectory);

    inline frc::PIDController g_PIDController { 
        std::ref(sKPDrivetrain), std::ref(sKIDrivetrain), std::ref(sKDDrivetrain) 
    };
}