#include "subsystem_headers/Arm.h"

void cb::Arm::activateSolenoid(bool onOff) {
    m_solenoid.Set(onOff);
}

void cb::Arm::moveLimb(units::volt_t voltage) {
    m_limb.SetVoltage(voltage);
}
