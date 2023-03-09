#ifndef MOVE_ARM
#define MOVE_ARM

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include <units/voltage.h>

#include "subsystem_headers/Arm.h"
#include "Constants.h"

namespace cb {
    //Move arm to the setpoint 0
    class MoveArm 
        : public frc2::CommandHelper<frc2::CommandBase, MoveArm>
    {
    private:
        double m_setpoint = 0;
        double m_direction = 1;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
    public:
        MoveArm(double setpoint);
    };
}

#endif