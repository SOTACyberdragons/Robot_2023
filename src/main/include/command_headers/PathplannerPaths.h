#include <pathplanner/lib/PathPlanner.h>

namespace cb {
    using namespace pathplanner;

    enum class PathName {
        BLUE1_LEFT_CHARGE,
        BLUE3_RIGHT_CHARGE,
        RED4_LEFT_CHARGE,
        TEST
    };

    frc::Trajectory loadPath(PathName path, 
        units::meters_per_second_t maxVel, units::meters_per_second_squared_t maxAccel);
}