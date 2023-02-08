#include "command_headers/auto/DriveMeters.h"

frc2::Command *cb::driveMeters(units::meter_t meters)
{
    // prevents the robot from accelerating too fast
    frc::DifferentialDriveVoltageConstraint constraint(
        frc::SimpleMotorFeedforward<units::meter>(
            cb::ksDrivetrain, cb::kvDrivetrain, cb::kaDrivetrain),
        cb::kDriveKinematics, 2_V);

    // Set up config for trajectory
    frc::TrajectoryConfig config(cb::kMaxSpeed, cb::kMaxAcceleration);

    // Add kinematics to ensure max speed is actually obeyed
    config.SetKinematics(cb::kDriveKinematics);

    // Apply the voltage constraint
    config.AddConstraint(constraint);

    // An example trajectory to follow.  All units in meters.
    auto trajectory = frc::TrajectoryGenerator::GenerateTrajectory(
        frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
        {},
        frc::Pose2d(meters, 0_m, frc::Rotation2d(0_deg)),
        config);

    return new frc2::RamseteCommand(
        trajectory,
        [&]() { return g_drivetrain.getPose(); },
        frc::RamseteController(cb::kRamseteB, cb::kRamseteZeta),
        frc::SimpleMotorFeedforward<units::meters>(ksDrivetrain, kvDrivetrain, kaDrivetrain),
        kDriveKinematics,
        [&]() { return g_drivetrain.getWheelSpeeds(); },
        frc2::PIDController(kPDrivetrain, kIDrivetrain, kDDrivetrain),
        frc2::PIDController(kPDrivetrain, kIDrivetrain, kDDrivetrain),
        [&](auto left, auto right) { g_drivetrain.tankDriveVolts(left, right); },
        {&g_drivetrain}
    );
};