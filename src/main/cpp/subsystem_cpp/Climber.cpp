#include "subsystem_headers/Climber.h"

void cb::Climber::stopPivot() {
    m_primaryPivotMotor.Set(ControlMode::PercentOutput, 0);
}

void cb::Climber::stopArms() {
    m_primaryPivotMotor.Set(ControlMode::PercentOutput, 0);
}

void cb::Climber::movePivot(Direction direction) {
    if (direction == Direction::FORWARD) {
        m_primaryPivotMotor.Set(ControlMode::PercentOutput, kPivotSpeed);
    } else if (direction == Direction::BACKWARD) {
        m_primaryPivotMotor.Set(ControlMode::PercentOutput, -kPivotSpeed);
    } else {
        std::cout << "Error: Invalid direction passed to movePivot method in climber subsystem!\n";
    }
}

void cb::Climber::moveArms(Direction direction) {
    if (direction == Direction::UP) {
        m_primaryArmMotor.Set(ControlMode::PercentOutput, kArmSpeed);
    } else if (direction == Direction::DOWN) {
        m_primaryArmMotor.Set(ControlMode::PercentOutput, -kArmSpeed);
    } else {
        std::cout << "Error: Invalid direction passed to moveArms method in climber subsystem!\n";
    }
}

cb::Climber::Climber() {
    m_primaryPivotMotor.ConfigFactoryDefault();
    m_secondaryPivotMotor.ConfigFactoryDefault();

    // Set the pivot motor encoder's sensor phase (Don't change)
    m_primaryPivotMotor.SetSensorPhase(false);
    m_secondaryPivotMotor.SetSensorPhase(false);

    // Make sure the pivot motors are turning the right direction
    m_primaryPivotMotor.SetInverted(false);
        m_secondaryPivotMotor.SetInverted(true);

    // Behavior of the pivot motors under 0 power. Brake or coast
    m_primaryPivotMotor.SetNeutralMode(NeutralMode::Brake);
    m_secondaryPivotMotor.SetNeutralMode(NeutralMode::Brake);

    // We make the left a follower, so all commands need to be sent to the right
    // pivot motor
    m_secondaryPivotMotor.Follow(m_primaryPivotMotor);

    // Reset any embedded arm motor configurations
    m_primaryArmMotor.ConfigFactoryDefault();
    m_secondaryArmMotor.ConfigFactoryDefault();

    // The arm motors DON'T need to be inverted
    m_primaryArmMotor.SetInverted(false);
    m_secondaryArmMotor.SetInverted(false);

    // Behavior of the arm motors under 0 power. Brake or coast
    m_primaryArmMotor.SetNeutralMode(NeutralMode::Coast);
    m_secondaryArmMotor.SetNeutralMode(NeutralMode::Coast);

    // We make the left a follower, so all commands need to be sent to the right
    // arm motor
    m_secondaryArmMotor.Follow(m_primaryArmMotor);
}