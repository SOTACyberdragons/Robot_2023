#include "command_headers/ToggleFrontIntake.h"

void cb::ToggleFrontIntake::Initialize() {
    std::cout << "Running handoff\n";
    //AddRequirements(&g_frontIntake);
    //g_frontIntake.used = true;

    if (g_frontIntake.up()) {
        //std::cout << "Going up\n";
        m_direction = -1;
    } else {
        m_direction = 1;
    } 
}

void cb::ToggleFrontIntake::Execute() {
    //std::cout << "Handing off intake\n";
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
    std::cout << "Done with intake\n";
    g_frontIntake.changeDirection(0); //stop moving intake motor
}

cb::ToggleFrontIntake::ToggleFrontIntake(bool handoff) 
    : m_handoff(handoff)
{}