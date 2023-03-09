#ifndef FRONT_INTAKE
#define FRONT_INTAKE

#include <frc2/command/SubsystemBase.h>

#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>

#include "Constants.h"

using ctre::phoenix::motorcontrol::can::WPI_TalonFX;
using ctre::phoenix::motorcontrol::can::WPI_TalonSRX;

namespace cb {
    class FrontIntake : public frc2::SubsystemBase {
    private:
        WPI_TalonFX m_directionMaster { FRONT_INTAKE_TALON_FX_ID };
        WPI_TalonSRX m_wheelMaster { FRONT_INTAKE_TALON_SRX_ID };
    public:
        FrontIntake();

        double getFXSensorPos();

        void changeDirection(double power);
        void spinWheels(double power);

        void setFXSensorPosition(double pos);
    };

    inline FrontIntake g_frontIntake;
}

#endif