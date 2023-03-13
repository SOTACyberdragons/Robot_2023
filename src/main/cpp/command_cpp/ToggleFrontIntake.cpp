#include "command_headers/ToggleFrontIntake.h"

void cb::ToggleFrontIntake::Initialize() {
    AddRequirements(&g_frontIntake);
    //g_frontIntake.used = true;

    if (g_frontIntake.down()) {
        std::cout << "Going up\n";
        m_direction = 1;
    } else if (g_frontIntake.up()) {
        if (m_handoff) {
            Cancel();
        } else {
            m_direction = -1;
        }
    } else { //do not allow command to be used while intake is moving
        Cancel();
    }
}

void cb::ToggleFrontIntake::Execute() {
    g_frontIntake.changeDirection(frontIntakeDirPower * m_direction);
}

bool cb::ToggleFrontIntake::IsFinished() {
    if (m_direction == 1) { //if we are going up
        return g_frontIntake.up();
    } else { //otherwise 
        return g_frontIntake.down();
    }
}

void cb::ToggleFrontIntake::End(bool m_isFinished) {
    g_frontIntake.changeDirection(0); //stop moving intake motor
}

cb::ToggleFrontIntake::ToggleFrontIntake(bool handoff) 
    : m_handoff(handoff)
{}