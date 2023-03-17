#ifndef MOVE_ARM_TO_INTAKE
#define MOVE_ARM_TO_INTAKE

#include <map>

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include "subsystem_headers/Arm.h"

namespace cb {
    enum class ArmPosition {
        CUBE_POS,
        CONE_POS
    };

    class MoveArmToIntake 
        : public frc2::CommandHelper<frc2::CommandBase, MoveArmToIntake>
    {
    private:
        double m_setpoint = 0;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool);
    public:
        MoveArmToIntake(ArmPosition Pos);
    };
}

#endif