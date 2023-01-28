#include "command_headers/ClimberArms.h"

void cb::ClimberArms::Execute() {
    g_climber.moveArms(m_direction);
}

void cb::ClimberArms::End(bool interrupted) {
    g_climber.stopArms();
}

cb::ClimberArms::ClimberArms(Direction direction) 
    : m_direction(direction) 
{
    AddRequirements(&g_climber);
}