#include "subsystem_headers/FrontIntake.h"

void cb::FrontIntake::Periodic() {
    
}

cb::FrontIntake::FrontIntake()
{
    m_directionMaster.SetSelectedSensorPosition(frontIntakeDownPos);
    m_doubleSolenoid.Set(frc::DoubleSolenoid::Value::kForward);
}

bool cb::FrontIntake::down() {
    return !m_lowerSwitch.Get();
}

bool cb::FrontIntake::up() {
    return !m_upperSwitch.Get();
}

bool cb::FrontIntake::isClosed() const {
    return m_doubleSolenoid.Get() == SolenoidState::kReverse;
}

double cb::FrontIntake::getFXSensorPos()
{
    return m_directionMaster.GetSelectedSensorPosition();
}

void cb::FrontIntake::changeDirection(double power)
{
    m_directionMaster.Set(power);
}

void cb::FrontIntake::spinWheels(double power)
{
    m_wheelMaster.Set(power);
}

void cb::FrontIntake::toggleJaws()
{
    m_doubleSolenoid.Toggle();
}

void cb::FrontIntake::setFXSensorPosition(double pos)
{
    std::cout << "Position: " << pos << std::endl;
    m_directionMaster.SetSelectedSensorPosition(pos);
    std::cout << "Set to " << m_directionMaster.GetSelectedSensorPosition() << std::endl;
}