#include "command_headers/Climb.h"

void cb::Climb::Initialize() {
    AddRequirements(&g_drivetrain); 
    
    //reset climbing state variables
    m_lastRoll = g_drivetrain.getGyro().GetRoll();
    m_minRoll = m_lastRoll;
    m_maxRoll = m_lastRoll;
    m_voltage = toRampVoltage;
    m_onRamp = false;
    m_isFinished = false;

    std::cout << "Goal: " << m_goal.to<double>() << std::endl;
}

void cb::Climb::Execute() {
    double currentRoll = g_drivetrain.getGyro().GetRoll();

    m_deltaRoll = currentRoll - m_lastRoll;
    m_lastRoll = currentRoll;

    //experiments show minimum roll is approximately -18
    m_minRoll = std::min(m_minRoll, currentRoll);
    //m_maxRoll = std::max(m_maxRoll, currentRoll);

    double deltaY = std::abs(g_drivetrain.getPose().Y().to<double>() - m_yCoord.to<double>());

    using namespace std::chrono_literals;

    if (!m_onRamp && m_minRoll < 2 - forwardRampRollThreshold) {
        m_onRamp = true;
        m_yCoord = g_drivetrain.getPose().Y();
        m_voltage = onRampVoltage;
        std::cout << "On the ramp\n";
    } else if (m_onRamp && deltaY > m_goal.to<double>()) {
        m_isFinished = true;
        m_voltage = 0_V;
    } else if (m_onRamp) {
        m_voltage = onRampVoltage + (toRampVoltage - onRampVoltage) * (m_goal.to<double>() - deltaY) / m_goal.to<double>();
    }

    g_drivetrain.tankDriveVolts(m_voltage, m_voltage);
}

bool cb::Climb::IsFinished() {
    return m_isFinished;
}

void cb::Climb::End(bool) {
    //g_drivetrain.setMotorMode(NeutralMode::Brake);
    g_drivetrain.tankDriveVolts(0_V, 0_V);
    g_drivetrain.setMotorMode(NeutralMode::Brake);
}

void cb::Climb::setGoal(units::meter_t meters) {
    m_goal = meters;
}

cb::Climb::Climb(units::meter_t meters)
    : m_goal(meters)
{}
    