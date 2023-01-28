#include <frc2/command/SubsystemBase.h>

#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>

#include "Constants.h"

using ctre::phoenix::motorcontrol::can::WPI_TalonSRX;
using ctre::phoenix::motorcontrol::ControlMode;

namespace cb {
    class Intake : public frc2::SubsystemBase {
    private:
        WPI_TalonSRX intakeMotor { INTAKE_MOTOR_ID };
    public:
        //power arg must be negative if we are not stopping the motor. 
        //To stop the motor pass in 0
        void setPower(double power);
    };
}