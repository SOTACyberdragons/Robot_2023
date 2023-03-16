#include "subsystem_headers/Arm.h"

void cb::Arm::Periodic() {
    if (!m_limitSwitch.Get()) { //if the arm has passed the motors
       m_limb.SetSelectedSensorPosition(0);
    }
}

double cb::Arm::feedForward() {
    double degreeAngle = m_limb.GetSelectedSensorPosition() / 968.1454;
    double radianAngle = (degreeAngle * pi) / 180;
    return sin(radianAngle) * 0.05;
}

cb::Arm::Arm() {
    m_limb.SetSelectedSensorPosition(0);
    m_limb.SetNeutralMode(NeutralMode::Brake);
    m_pcm.EnableCompressorDigital();
    m_solenoid.Set(frc::DoubleSolenoid::Value::kReverse);
}

const WPI_TalonFX& cb::Arm::getMotor() const {
    return m_limb;
}

bool cb::Arm::getLimitSwitchState() const {
    return m_limitSwitch.Get();
}

void cb::Arm::toggleArmBase() {
    m_solenoid.Toggle();
}

double cb::Arm::getSensorPos() {
    return m_limb.GetSelectedSensorPosition();
}

void cb::Arm::resetPosition() {
    m_limb.SetSelectedSensorPosition(0);
}

void cb::Arm::moveLimb(double voltage) {
    if (voltage >= -0.05 && voltage <= 0.05) {
        if (usingFeedForward) {
            m_limb.Set(feedForward());
        } else {
            m_limb.Set(0);
        }
    } else {
        m_limb.Set(voltage * maxArmVoltage);
    }
}