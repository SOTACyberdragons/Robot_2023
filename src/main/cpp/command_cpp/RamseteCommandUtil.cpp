#include "command_headers/RamseteCommandUtil.h"

frc2::RamseteCommand cb::ramseteCommand(units::meter_t meters)
{
    // prevents the robot from accelerating too fast
    frc::DifferentialDriveVoltageConstraint constraint(
        frc::SimpleMotorFeedforward<units::meter>(
            cb::ksDrivetrain, cb::kvDrivetrain, cb::kaDrivetrain),
        cb::kDriveKinematics, 4_V);
    // Set up config for trajectory
    frc::TrajectoryConfig config(1_mps, 1_mps_sq);

    // Add kinematics to ensure max speed is actually obeyed
    config.SetKinematics(cb::kDriveKinematics);

    // Apply the voltage constraint
    config.AddConstraint(constraint);

    frc::Pose2d robotPosition = g_drivetrain.getPose();
    units::meter_t x = robotPosition.X(), y = robotPosition.Y();
    
    auto trajectory = frc::TrajectoryGenerator::GenerateTrajectory(
        frc::Pose2d(x, y, frc::Rotation2d(0_deg)), //startpoint
        {}, //no interior waypoints
        frc::Pose2d(x + meters, y, frc::Rotation2d(0_deg)), //endpoint
        config);

    return frc2::RamseteCommand(
        trajectory,
        [&]() { return g_drivetrain.getPose(); },
        frc::RamseteController(cb::kRamseteB, cb::kRamseteZeta),
        frc::SimpleMotorFeedforward<units::meters>(ksDrivetrain, kvDrivetrain, kaDrivetrain),
        kDriveKinematics,
        [&]() { return g_drivetrain.getWheelSpeeds(); },
        std::ref(g_PIDController),
        std::ref(g_PIDController),
        [&](units::volt_t left, units::volt_t right) { g_drivetrain.tankDriveVolts(left, right); },
        {&g_drivetrain}
    );
};

frc2::RamseteCommand cb::ramseteCommand(frc::Trajectory trajectory) {
    return frc2::RamseteCommand(
        trajectory,
        [&]() { return g_drivetrain.getPose(); },
        frc::RamseteController(cb::kRamseteB, cb::kRamseteZeta),
        frc::SimpleMotorFeedforward<units::meters>(ksDrivetrain, kvDrivetrain, kaDrivetrain),
        kDriveKinematics,
        [&]() { return g_drivetrain.getWheelSpeeds(); },
        std::ref(g_PIDController),
        std::ref(g_PIDController),
        [&](units::volt_t left, units::volt_t right) { g_drivetrain.tankDriveVolts(left, right); },
        {&g_drivetrain}
    );
}