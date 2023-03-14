#include <chrono>

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include <units/voltage.h>
#include <units/length.h>

#include "subsystem_headers/Drivetrain.h"

namespace cb {
    using namespace std::chrono;
    using namespace std::chrono_literals;

    class StayBalanced 
        : public frc2::CommandHelper<frc2::CommandBase, StayBalanced>
    {
    private:
        bool m_finished = true;

        units::meters_per_second_t m_lastSpeed = 0_mps;
        units::meters_per_second_t m_deltaSpeed = 0_mps;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
    };
}