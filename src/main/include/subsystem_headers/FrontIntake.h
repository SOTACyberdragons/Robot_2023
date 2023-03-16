#ifndef FRONT_INTAKE
#define FRONT_INTAKE

#include <iostream>

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>
#include <frc/DigitalInput.h>

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

        frc::DoubleSolenoid m_doubleSolenoid { 
            PCM_ID, frc::PneumaticsModuleType::CTREPCM,
            INTAKE_SOLENOID_FORWARD_CHANNEL_ID, INTAKE_SOLENOID_REVERSE_CHANNEL_ID
        };
        using SolenoidState = frc::DoubleSolenoid::Value;
        SolenoidState m_solenoidState = SolenoidState::kOff;

        frc::DigitalInput m_upperSwitch { UPPER_LIMIT_SWITCH_CHANNEL };
        frc::DigitalInput m_lowerSwitch { LOWER_LIMIT_SWITCH_CHANNEL };
        
        bool m_intakeUp = false;

        bool m_setDoubleSolenoid = false;

        void Periodic() override;
    public:
        FrontIntake();

        bool up();
        bool down();
        
        bool isClosed() const;

        double getFXSensorPos();

        void changeDirection(double power);
        void spinWheels(double power);
        
        void toggleJaws();

        void setFXSensorPosition(double pos);
    };

    inline FrontIntake g_frontIntake;
}

#endif