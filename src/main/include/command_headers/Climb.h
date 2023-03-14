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

/*
There are 2 states of climbing: getting onto the ramp and then driving to the middle.
A change in the roll of the gyro of more than 0.3 signifies a change, the first one being 
when the backside of the ramp goes up, and the second one being when the robot rotates down to the 
middle. The command ends when the 2nd change happens
*/

    class Climb
        : public frc2::CommandHelper<frc2::CommandBase, Climb>
    {
    private:
        double m_minRoll = 0, m_maxRoll = 0;

        units::meter_t m_yCoord = 0_m, m_goal = 0_m;

        double m_deltaRoll = 0;
        double m_lastRoll = 0;

        bool m_onRamp = false;
        bool m_isFinished = false;

        units::volt_t m_voltage = 0_V;

        //Point in time when robot moved onto the ramp
        time_point<high_resolution_clock> m_rampTime;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool) override;
    public:
        Climb(units::meter_t meters);
    };
}

