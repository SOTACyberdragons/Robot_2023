#include <iostream>

#include <frc2/Command/SubsystemBase.h>
#include <frc/Errors.h>

#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>

#include "Constants.h"

using ctre::phoenix::motorcontrol::can::WPI_TalonSRX;
using ctre::phoenix::motorcontrol::NeutralMode;
using ctre::phoenix::motorcontrol::ControlMode;

namespace cb {
    enum class Direction {
        FORWARD,
        BACKWARD,
        UP,
        DOWN
    };

    class Climber : public frc2::SubsystemBase {
    private:
        double kArmSpeed = 1;
        double kPivotSpeed = 0.75;

        WPI_TalonSRX m_primaryPivotMotor { PRIMARY_PIVOT_MOTOR_ID };
        WPI_TalonSRX m_secondaryPivotMotor { SECONDARY_PIVOT_MOTOR_ID };

        WPI_TalonSRX m_primaryArmMotor { PRIMARY_ARM_MOTOR_ID };
        WPI_TalonSRX m_secondaryArmMotor { SECONDARY_ARM_MOTOR_ID };
    public:
        void stopPivot();
        void stopArms();
        
        void movePivot(Direction direction);
        void moveArms(Direction direction);

        Climber();
    };
}