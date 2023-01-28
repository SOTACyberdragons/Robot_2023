#include "Subsystem_Headers/Feeder.h"

bool cb::Feeder::getBreakBeam() {
    return m_breakBeam.Get();
}

void cb::Feeder::setPower(double power) {
    m_feederMotor.Set(ControlMode::PercentOutput, power);
}