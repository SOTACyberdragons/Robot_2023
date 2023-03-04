#include "subsystem_headers/Arm.h"

// void cb::Arm::activateSolenoid(bool onOff) {
//     m_solenoid.Set(onOff);
// }

void cb::Arm::Periodic() {
    // if (m_magnetSensor.Get()) { //if the arm has passed the motors
    //    m_limb.SetSelectedSensorPosition(0);
    // }
}

units::volt_t cb::Arm::feedForward() {
    double degreeAngle = m_limb.GetSelectedSensorPosition() / 69.45;
    double radianAngle = (degreeAngle * pi) / 180;

    return units::volt_t(sin(radianAngle));
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

    m_limb.SetVoltage(voltage + feedForward());
}
