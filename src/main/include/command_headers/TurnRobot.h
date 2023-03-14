#include <math.h>

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include <units/angle.h>

#include "subsystem_headers/Drivetrain.h"
#include "Constants.h"

namespace cb
{
    class TurnRobot
        : public frc2::CommandHelper<frc2::CommandBase, TurnRobot>
    {
    private:
        double m_initialDegree = 0;
        double m_degree = 0;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool) override;
    public:
        TurnRobot(double degree);
    };
}