#include <math.h>
#include <chrono>
#include <thread>
 
#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include <units/voltage.h>

#include "subsystem_headers/Drivetrain.h"

namespace cb
{
    class Climb
        : public frc2::CommandHelper<frc2::CommandBase, Climb>
    {
    private:
        bool m_finished = false;

        units::volt_t m_voltage = 3_V;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
    };
}

