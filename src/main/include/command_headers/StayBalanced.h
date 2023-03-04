#include <chrono>

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include <units/voltage.h>

#include "subsystem_headers/Drivetrain.h"

namespace cb {
    using namespace std::chrono;
    using namespace std::chrono_literals;

    class StayBalanced 
        : public frc2::CommandHelper<frc2::CommandBase, StayBalanced>
    {
    private:
        time_point<high_resolution_clock> m_startTime;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
    };
}