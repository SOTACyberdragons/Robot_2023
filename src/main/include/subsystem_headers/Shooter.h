#include <frc2/command/SubsystemBase.h>

#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>

#include "Constants.h"

using ctre::phoenix::motorcontrol::can::WPI_TalonFX;
using ctre::phoenix::motorcontrol::NeutralMode;
using ctre::phoenix::motorcontrol::ControlMode;

namespace cb {
    class Shooter : public frc2::SubsystemBase {
    private:
        WPI_TalonFX m_leftMotor { cb::LEFT_SHOOTER_MOTOR_ID };
        WPI_TalonFX m_rightMotor { cb::RIGHT_SHOOTER_MOTOR_ID };
    public:
        static constexpr double kSensorUnitsPerRotation = 2048;
        
        double getRPS();

        double getPower();
        void setPower(double powerLevel);

        void zeroSensors();

        Shooter();
    };
}