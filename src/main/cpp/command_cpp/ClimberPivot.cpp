#include "command_headers/ClimberPivot.h"

void cb::ClimberPivot::Execute() {
    g_climber.movePivot(m_direction);
}

void cb::ClimberPivot::End(bool interrupted) {
    g_climber.stopPivot();
}

cb::ClimberPivot::ClimberPivot(Direction direction) 
    : m_direction(direction) 
{
    AddRequirements(&g_climber);
}