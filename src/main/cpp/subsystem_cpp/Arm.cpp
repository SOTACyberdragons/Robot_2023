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
    m_limb.SetSelectedSensorPosition(0);
}

const WPI_TalonFX& cb::Arm::getMotor() const {
    return m_limb;
}
 
double cb::Arm::getSensorPos() {
    return m_limb.GetSelectedSensorPosition();
}

void cb::Arm::resetPosition() {
    m_limb.SetSelectedSensorPosition(0);
}

void cb::Arm::moveLimb(units::volt_t voltage) {
    std::cout << m_limb.GetSelectedSensorPosition() << std::endl;

    units::volt_t feedForward = 
        units::volt_t(0.2 * sin(((m_limb.GetSelectedSensorPosition() * pi) / 180)));

    m_limb.SetVoltage(voltage);
}
