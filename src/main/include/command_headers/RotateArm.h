#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include "subsystem_headers/Arm.h"

namespace cb {
    class RotateArm 
        : public frc2::CommandHelper<frc2::CommandBase, RotateArm> 
    {
    private:
        double m_setpoint = 0;
        double m_deadBand = 0;

        double m_direction = 1;

        void Initialize() override;
        bool IsFinished() override;
    public:
        RotateArm(double setpoint, double deadband);
    };
}