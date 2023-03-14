#ifndef ARM_INTAKE
#define ARM_INTAKE

#include <frc2/command/SubsystemBase.h>

#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>

#include <units/voltage.h>

#include "Constants.h"

using ctre::phoenix::motorcontrol::can::WPI_TalonSRX;

namespace cb {
    class ArmIntake : public frc2::SubsystemBase {
    private:
        WPI_TalonSRX m_talon { ARM_INTAKE_ID };
    public:
        void grab(double axis);

        ArmIntake();
    };

    inline ArmIntake g_armIntake;
}

#endif