#include "subsystem_headers/Arm.h"

// void cb::Arm::activateSolenoid(bool onOff) {
//     m_solenoid.Set(onOff);
// }

void cb::Arm::Periodic() {
    // if (m_magnetSensor.Get()) { //if the arm has passed the motors
    //    m_limb.SetSelectedSensorPosition(0);
    // }
}

cb::Arm::Arm() {
    m_limb.SetInverted(true);
}

const WPI_TalonFX& cb::Arm::getMotor() const {
    return m_limb;
}

//positive voltage for going up, negative for going down
void cb::Arm::moveLimb(units::volt_t voltage) {
    static bool stopped = false;
    
    if (stopped && voltage < -0.5_V) {
        m_limb.SetVoltage(0_V);
        return;
    }
      
    //if we are moving the arm down check for hard stop
    if (voltage < -0.5_V && m_limb.GetSelectedSensorPosition() < -261406) { 
        m_limb.SetVoltage(0_V);
        stopped = true;
        return;
    } 

    stopped = false;
    
    m_limb.SetVoltage(voltage);
}
