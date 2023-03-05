#ifndef MOVE_ARM
#define MOVE_ARM

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>

#include <units/voltage.h>

#include "subsystem_headers/Arm.h"
#include "Constants.h"

namespace cb {
<<<<<<< HEAD
    //Move arm to the setpoint 0
=======
>>>>>>> 658096c3e1fe0d16c25514170a2627d8b61df4f3
    class MoveArm 
        : public frc2::CommandHelper<frc2::CommandBase, MoveArm>
    {
    private:
        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
    };
}

#endif