// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

void cb::Robot::RobotInit() {
  std::cout << "Vader initializing\n";

  g_arm.resetPosition();

  addAutoModeOptions();
}

void cb::Robot::RobotPeriodic() {
  frc2::CommandScheduler::GetInstance().Run();
}

void cb::Robot::AutonomousInit() {
  m_autoCommand = getSelectedAutoCommand();

  if (m_autoCommand != nullptr) {
    m_autoCommand->Schedule();
  }
}

void cb::Robot::AutonomousPeriodic() {}

void cb::Robot::AutonomousExit() {
  g_drivetrain.tankDriveVolts(0_V, 0_V);
}

void cb::Robot::TeleopInit() {
  configureButtonBindings(); //map buttons
}

void cb::Robot::TeleopPeriodic() {
  
}

void cb::Robot::DisabledInit() {
  frc2::CommandScheduler::GetInstance().CancelAll(); //cancel all commands
  g_drivetrain.resetTalons();
  g_drivetrain.resetDistance();

  //the position of the robot doesn't get fully reset to 0, 0
  g_drivetrain.resetPosition();
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
