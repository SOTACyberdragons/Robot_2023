#include "subsystem_headers/Shooter.h"

double cb::Shooter::getRPS() {
    double ticksPerSample = m_rightMotor.GetSelectedSensorVelocity();
    double ticksPerSecond = ticksPerSample * 10;
    double rps = ticksPerSecond / kSensorUnitsPerRotation;
    return rps;
}

double cb::Shooter::getPower() {
    return m_rightMotor.Get();
}

void cb::Shooter::setPower(double powerLevel) {
    m_rightMotor.Set(ControlMode::PercentOutput, powerLevel);
}

void cb::Shooter::zeroSensors() {
    m_leftMotor.GetSensorCollection().SetIntegratedSensorPosition(0, kTimeoutMs);
    m_rightMotor.GetSensorCollection().SetIntegratedSensorPosition(0, kTimeoutMs);
}

cb::Shooter::Shooter() {
    // Reset any embedded the motor configurations
    m_leftMotor.ConfigFactoryDefault();
    m_leftMotor.ConfigFactoryDefault();

    // Set the motor encoder's sensor phase (Don't change)
    m_leftMotor.SetSensorPhase(false);
    m_rightMotor.SetSensorPhase(false);

    // Make sure the motors are turning the right direction
    m_leftMotor.SetInverted(true);
    m_rightMotor.SetInverted(false);

    // Behavior of the motors under 0 power. Brake or coast
    m_leftMotor.SetNeutralMode(NeutralMode::Coast);
    m_rightMotor.SetNeutralMode(NeutralMode::Coast);

    // We make the left a follower, so all commands need to be sent to the right motor
    m_leftMotor.Follow(m_rightMotor);

    // Finally, clean up on Talon data
    zeroSensors();
}