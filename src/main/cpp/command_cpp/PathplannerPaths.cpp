#include "command_headers/PathplannerPaths.h"

frc::Trajectory cb::loadPathplannerPath(PathName path, 
    units::meters_per_second_t maxAcceleration, units::meters_per_second_squared_t maxVelocity) 
{
    std::string pathPath;

    switch (path) {
        case PathName::BLUE1_LEFT_CHARGE:
            pathPath = "Pathplanner/Blue1_Left_Charge.path";
            break;
        case PathName::BLUE3_RIGHT_CHARGE:
            pathPath = "Pathplanner/Blue1_Right_Charge.path";
            break;
        case PathName::RED4_LEFT_CHARGE:
            pathPath = "Pathplanner/Red4_Left_Charge.path";
            break;
    }

    auto trajectory = PathPlanner::loadPath(pathPath, PathConstraints(maxAcceleration, maxVelocity));

    return trajectory.asWPILibTrajectory();
}