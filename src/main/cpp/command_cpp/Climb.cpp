#include "command_headers/Climb.h"

void cb::Climb::Initialize() {
    AddRequirements(&g_drivetrain);

    // INITIAL CONDITIONS: The operator must orient the robot:
    //      - on the flat
    //      - facing ("mouth" end towards) the ramp
    State m_state = State::Approach;
    Direction m_direction = Direction::Forward;
    m_rollSmoothWindow::Clear();
    m_rollDeltaWindow::Clear();

    //reset climbing state variables
    m_lastRoll = g_drivetrain.getGyro().GetRoll();
    m_minRoll = m_lastRoll;
    m_maxRoll = m_lastRoll;
    m_voltage = toRampVoltage;
    m_onRamp = false;
    m_isFinished = false;
}

void cb::Climb::Execute() {

    // Linear interplation between at0 to at1. 0 <= frac <= 1.
    double lerp(double frac, double at0, double at1) {
        return at0 + frac * (at1 - at0);
    }

    // Fraction (from 0 to 1) of absolute values.
    double absfrac(double numerator, double denominator) {
        const double abs_denominator = std::abs(denominator);
        return std::max(1, (std::abs(numerator) - abs_denominator) / abs_denominator);
    }

    double currentRoll = g_drivetrain.getGyro().GetRoll();

    m_deltaRoll = currentRoll - m_lastRoll;
    m_lastRoll = currentRoll;

    //experiments show minimum roll is approximately -18
    m_minRoll = std::min(m_minRoll, currentRoll);
    //m_maxRoll = std::max(m_maxRoll, currentRoll);

    // Get smoothed roll and delta roll.
    m_rollSmoothWindow::Insert(currentRoll);
    const double smoothRoll = m_rollSmoothWindow::Mean();
    m_rollDeltaWindow::Insert(smoothRoll);
    const double previousRoll = m_rollDeltaWindow::Previous();
    const double deltaRoll = m_rollDeltaWindow::Delta();
    // TODO: validate all these magic numbers!
    const bool isFlat = std::abs(smoothRoll) < 3;
    const bool isRolled = std::abs(smoothRoll) > 5;
    const bool isFlattening = std::abs(previousRoll) - std::abs(smoothRoll) > 5;

    const double deltaY = std::abs(g_drivetrain.getPose().Y().to<double>() - m_yCoord.to<double>());
    const double progressY = absfrac(deltaY, m_goal.to<double>()); // 0 <= progressY <= 1
    const bool isDoneProgressY = std::abs(progressY - 1) < 0.01;

    using namespace std::chrono_literals;

    switch(m_state)
    {
        case State::Approach:
            m_voltage = toRampVoltage;
            if (isRolled) {
                m_yCoord = g_drivetrain.getPose().Y(); // set start for progressY
                m_state = State::Ascend;
            }
            break;
        case State::Ascend:
            m_voltage = lerp(progressY, onRampVoltage, toRampVoltage);
            // if (isFlat) {
            // if (isFlattening) {
            if (isDoneProgressY) {
                m_state = State::Balance;
                m_isFinished = true;
                m_voltage = 0_V;
            }
            break;
        case State::Balance:
            break;
        case State::Clear:
            break;
        case State::Orient:
            break;
    }

    if (m_direction == Direction::Backward) {
        m_voltage = - m_voltage;
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

cb::Climb::Climb(units::meter_t meters)
    : m_goal(meters)
{}
 
