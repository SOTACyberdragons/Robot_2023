#include "subsystem_headers/FrontIntake.h"

cb::FrontIntake::FrontIntake() {
    m_directionMaster.SetSelectedSensorPosition(frontIntakeDownPos);
}

double cb::FrontIntake::getFXSensorPos() {
    return m_directionMaster.GetSelectedSensorPosition();
}

void cb::FrontIntake::changeDirection(double power) {
    m_directionMaster.Set(power);
}

void cb::FrontIntake::spinWheels(double power) {
    m_wheelMaster.Set(power);
}

void cb::FrontIntake::setFXSensorPosition(double pos) {
    m_directionMaster.SetSelectedSensorPosition(pos);
}