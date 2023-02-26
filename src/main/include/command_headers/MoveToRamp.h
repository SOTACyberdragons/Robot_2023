#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include <pathplanner/lib/PathPlanner.h>

#include "subsystem_headers/Drivetrain.h"
#include "Constants.h"

namespace cb {
    using namespace pathplanner;

    PathPlannerTrajectory Blue1ToLeftCharge();

    class MoveToRamp
        : public frc2::CommandHelper<frc2::CommandBase, MoveToRamp> 
    {
    private:
        double m_lastRoll = 0;
        double m_deltaRoll = 0;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
    };
}
