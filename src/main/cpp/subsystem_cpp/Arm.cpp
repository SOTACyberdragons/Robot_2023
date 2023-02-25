#include "subsystem_headers/Arm.h"

// void cb::Arm::activateSolenoid(bool onOff) {
//     m_solenoid.Set(onOff);
// }

cb::Arm::Arm() {
    m_limb.SetInverted(true);
}

void cb::Arm::moveLimb(units::volt_t voltage) {
    //std::cout << "Sensor Position: " << m_limb.GetSelectedSensorPosition() << std::endl;
    //std::cout << "Voltage: " << voltage.to<double>() << std::endl;
    m_limb.SetVoltage(voltage);
}
