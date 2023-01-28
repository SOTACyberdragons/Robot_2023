#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include "RobotContainer.h"

namespace cb {
    class ClimberArms : public frc2::CommandHelper<frc2::CommandBase, ClimberArms> {
    private:
        Direction m_direction;

        virtual void Execute() override;
        virtual void End(bool interrupted) override;
    public:
        explicit ClimberArms(Direction direction);
    };
}