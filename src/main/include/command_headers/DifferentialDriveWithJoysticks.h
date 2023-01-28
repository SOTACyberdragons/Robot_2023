#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include "RobotContainer.h"

namespace cb {
    class DifferentialDriveWithJoysticks : 
        public frc2::CommandHelper<frc2::CommandBase, DifferentialDriveWithJoysticks> {
    private:
        virtual void Execute() override;
    public:
        DifferentialDriveWithJoysticks();
    };
}