
#ifndef CLIMBER_PIVOT
#define CLIMBER_PIVOT

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include "RobotContainer.h"

namespace cb {
    class ClimberPivot : public frc2::CommandHelper<frc2::CommandBase, ClimberPivot> {
    private:
        Direction m_direction;

        virtual void Execute() override;
        virtual void End(bool interrupted) override;
    public:
        explicit ClimberPivot(Direction direction);
    };
}

#endif