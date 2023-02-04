#include "command_headers/auto/DriveClimb.h"

frc2::Command* cb::driveClimb() {
    //prevents the robot from accelerating too fast
//     frc::DifferentialDriveVoltageConstraint constraint(
//         frc::SimpleMotorFeedforward<units::meter>(
//             cb::ksDrivetrain, cb::kvDrivetrain, cb::kaDrivetrain),
//             cb::kDriveKinematics, 10_V);
    
//   //Set up config for trajectory
//   frc::TrajectoryConfig config(cb::kMaxSpeed,
//                                cb::kMaxAcceleration);
//   // Add kinematics to ensure max speed is actually obeyed
//   config.SetKinematics(cb::kDriveKinematics);
//   // Apply the voltage constraint
//   config.AddConstraint(constraint);

//   // An example trajectory to follow.  All units in meters.
//   auto exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
//       // Start at the origin facing the +X direction
//       frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
//       // Pass through these two interior waypoints, making an 's' curve path
//       {frc::Translation2d(1_m, 1_m), frc::Translation2d(2_m, -1_m)},
//       // End 3 meters straight ahead of where we started, facing forward
//       frc::Pose2d(3_m, 0_m, frc::Rotation2d(0_deg)),
//       // Pass the config
//       config);
    
//     frc2::RamseteCommand ramseteCommand(
//       exampleTrajectory, [&]() { return g_drivetrain.getPose(); },
//       frc::RamseteController(cb::kRamseteB,
//                              cb::kRamseteZeta),
//       frc::SimpleMotorFeedforward<units::meters>(
//           cb::ksDrivetrain, cb::kvDrivetrain, cb::kaDrivetrain),
//       cb::kDriveKinematics,
//       [&] { return g_drivetrain.getWheelSpeeds(); },
//       frc2::PIDController(cb::kPDrivetrain, 0, 0),
//       frc2::PIDController(cb::kPDrivetrain, 0, 0),
//       [&](auto left, auto right) { g_drivetrain.tankDriveVolts(left, right); },
//       {&g_drivetrain});

//   // Reset odometry to the starting pose of the trajectory.
//   g_drivetrain.resetOdometry(exampleTrajectory.InitialPose());

//   // no auto
//   return new frc2::SequentialCommandGroup(
//       std::move(ramseteCommand),
//       frc2::InstantCommand([&] { g_drivetrain.tankDriveVolts(0_V, 0_V); }, {}));
    return nullptr;
};