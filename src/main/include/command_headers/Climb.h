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
        double m_lastRoll = 0.0;

        bool m_onRamp = false;
        bool m_isFinished = false;

        units::volt_t m_voltage = 0_V;

        //Point in time when robot moved onto the ramp
        time_point<high_resolution_clock> m_rampTime;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
    };
}

