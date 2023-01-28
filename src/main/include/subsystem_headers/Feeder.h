#include <frc2/command/SubsystemBase.h>
#include <frc/DigitalInput.h>

#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>

#include "Constants.h"

using ctre::phoenix::motorcontrol::can::WPI_TalonSRX;
using ctre::phoenix::motorcontrol::ControlMode;

namespace cb {
    class Feeder : public frc2::SubsystemBase {
    private:
        WPI_TalonSRX m_feederMotor { FEEDER_MOTOR_ID };
        frc::DigitalInput m_breakBeam { 0 };
    public:
        bool getBreakBeam();

        //For the feeder to go in, pass in a negative percentage.
        //For the feeder to go out, pass in a positive percentage.
        //To stop the feeder pass in 0.
        void setPower(double power);
    };
}