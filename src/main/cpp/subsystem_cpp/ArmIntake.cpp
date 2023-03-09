#include "subsystem_headers/ArmIntake.h"

void cb::ArmIntake::grab(double axis) {
    m_talon.Set(axis * maxArmIntakePower);
}