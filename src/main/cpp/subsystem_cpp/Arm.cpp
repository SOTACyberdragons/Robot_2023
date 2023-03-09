#include "subsystem_headers/Arm.h"

void cb::Arm::activateSolenoid(bool onOff) {
    //m_pcm.SetSolenoids()
    //m_solenoid.Set(onOff);
}

void cb::Arm::Periodic() {
    // if (m_magnetSensor.Get()) { //if the arm has passed the motors
    //    m_limb.SetSelectedSensorPosition(0);
    // }
}

double cb::Arm::feedForward() {
    double degreeAngle = m_limb.GetSelectedSensorPosition() / 968.1454;
    //std::cout << degreeAngle << std::endl;
    double radianAngle = (degreeAngle * pi) / 180;

    return sin(radianAngle) * 0.05;
}

cb::Arm::Arm() {
    m_limb.SetSelectedSensorPosition(0);
    m_limb.SetNeutralMode(NeutralMode::Brake);
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

void cb::Arm::moveLimb(double voltage) {
    if (voltage >= -0.05 && voltage <= 0.05) {
        m_limb.Set(feedForward());
    } else {
        m_limb.Set(voltage * 0.4);
    }
}