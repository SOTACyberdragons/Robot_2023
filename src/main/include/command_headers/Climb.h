#include <math.h>
#include <chrono>

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include <units/voltage.h>

#include "subsystem_headers/Drivetrain.h"

namespace cb
{
    using std::chrono::system_clock;

    class Climb
        : public frc2::CommandHelper<frc2::CommandBase, Climb>
    {
    private:
        bool m_finished = false;
        
        system_clock::time_point m_startTime = system_clock::now();

        bool m_onTop = false; //if we are on top of community zone

        void Initialize() override;
        /**
         * If the robot is on the ramp, keep sending power to that motor
         * When the vertical angle of the robot reaches 0, keep sending power to
         * the motors, but less, for a few seconds
         */
        void Execute() override;
        bool IsFinished() override;
    };
}