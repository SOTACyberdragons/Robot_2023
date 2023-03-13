#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include "subsystem_headers/FrontIntake.h"

namespace cb {
    class ToggleFrontIntake 
        : public frc2::CommandHelper<frc2::CommandBase, ToggleFrontIntake>
    {
    private:
        double m_direction = 1;

        const bool m_handoff;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
        void End(bool) override;
    public:
        ToggleFrontIntake(bool handoff);
    };
}