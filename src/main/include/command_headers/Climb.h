#include <math.h>
#include <chrono>
 
#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include <units/voltage.h>

#include "subsystem_headers/Drivetrain.h"

namespace cb
{
    using namespace std::chrono;
    using namespace std::chrono_literals;

    class Climb
        : public frc2::CommandHelper<frc2::CommandBase, Climb>
    {
    private:
        double m_deltaRoll = 0;

        time_point<high_resolution_clock> m_startTime;

        double m_lastRoll = 0.0;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
    };
}

