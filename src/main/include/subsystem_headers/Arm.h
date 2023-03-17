#ifndef ARM
#define ARM

#include <iostream>
#include <map>

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>
#include <frc/DigitalInput.h>
#include <frc/PneumaticsControlModule.h>

#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>

#include <units/voltage.h>

#include "Constants.h"

using ctre::phoenix::motorcontrol::can::WPI_TalonFX;
using ctre::phoenix::motorcontrol::NeutralMode;

namespace cb {
    class Arm : public frc2::SubsystemBase {
    private:
        frc::DigitalInput m_limitSwitch { LIMIT_SWITCH_CHANNEL_ID };
        frc::PneumaticsControlModule m_pcm { PCM_ID };
        
        frc::DoubleSolenoid m_solenoid { 
            PCM_ID, frc::PneumaticsModuleType::CTREPCM, 
            ARM_SOLENOID_FORWARD_CHANNEL_ID, ARM_SOLENOID_REVERSE_CHANNEL_ID
        };

        WPI_TalonFX m_limb { LIMB_ID };

        void Periodic() override;

        double feedForward();
    public:
        Arm();

        const WPI_TalonFX& getMotor() const;
        double getSensorPos(); 
        
        bool getLimitSwitchState() const;

        void toggleArmBase();

        void resetPosition();

        //positive voltage for going up, negative for going down
        void moveLimb(double voltage);
    };

   inline Arm g_arm;
}

#endif