#include "command_headers/PathplannerPaths.h"

frc::Trajectory cb::loadPath(PathName path, 
    units::meters_per_second_t maxAcceleration, units::meters_per_second_squared_t maxVelocity) 
{
    std::string pathPath;

    switch (path) {
        case PathName::BLUE1_LEFT_CHARGE:
            pathPath = "Blue1_Left_Charge";
            break;
        case PathName::BLUE3_RIGHT_CHARGE:
            pathPath = "Blue1_Right_Charge";
            break;
        case PathName::RED4_LEFT_CHARGE:
            pathPath = "Red4_Left_Charge";
            break;
        case PathName::TEST:
            pathPath = "Test";
            break;
    }

    auto trajectory = PathPlanner::loadPath(pathPath, PathConstraints(maxAcceleration, maxVelocity));

    return trajectory.asWPILibTrajectory();
}