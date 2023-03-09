#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include "subsystem_headers/FrontIntake.h"

namespace cb {
    class ToggleFrontIntake 
        : public frc2::CommandHelper<frc2::CommandBase, ToggleFrontIntake>
    {
    private:
        bool m_up = false;

        double m_direction = 1;

        double m_setpoint = 0;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool) override;
    };
}