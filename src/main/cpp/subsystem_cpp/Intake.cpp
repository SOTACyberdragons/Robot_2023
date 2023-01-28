#include "subsystem_headers/Intake.h"

void cb::Intake::setPower(double power) {
    intakeMotor.Set(ControlMode::PercentOutput, 0);
}