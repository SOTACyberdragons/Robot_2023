// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>

void cb::Robot::RobotInit() {
  std::cout << "Surge initializing\n";

  addAutoModeOptions();

  configureButtonBindings(); //map buttons
}

void cb::Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

void cb::Robot::AutonomousInit() {
  frc2::Command* command = getSelectedAutoCommand();

  if (command != nullptr) {
    command->Schedule();
  }
}

void cb::Robot::AutonomousPeriodic() {}

void cb::Robot::AutonomousExit() {}

void cb::Robot::TeleopInit() {
  frc2::CommandScheduler::GetInstance().SetDefaultCommand(&cb::g_drivetrain, cb::DifferentialDriveWithJoysticks());
}

void cb::Robot::TeleopPeriodic() {}

void cb::Robot::DisabledInit() {
  frc2::CommandScheduler::GetInstance().CancelAll(); //cancel all commands
  g_drivetrain.resetTalons();
  g_drivetrain.resetDistance();
}

void cb::Robot::DisabledPeriodic() {}

void cb::Robot::TestInit() {}

void cb::Robot::TestPeriodic() {}

void cb::Robot::SimulationInit() {}

void cb::Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<cb::Robot>();
}
#endif
