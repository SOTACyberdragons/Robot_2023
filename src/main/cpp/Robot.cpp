// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

void cb::Robot::updateSmartDashboardData() {
  frc::SmartDashboard::PutNumber("Roll", g_drivetrain.getGyro().GetRoll());
  frc::SmartDashboard::PutNumber("Yaw", g_drivetrain.getGyro().GetYaw());
  frc::SmartDashboard::PutNumber("Pitch", g_drivetrain.getGyro().GetPitch());
  frc::SmartDashboard::PutNumber("Left Wheel Velocity", g_drivetrain.getWheelSpeeds().left.to<double>());
  frc::SmartDashboard::PutNumber("Right Wheel Velocity", g_drivetrain.getWheelSpeeds().right.to<double>());
  frc::SmartDashboard::PutNumber("Arm Sensor Position", g_arm.getSensorPos());
  frc::SmartDashboard::PutNumber("Intake FX Sensor Position", g_frontIntake.getFXSensorPos());
  frc::SmartDashboard::PutBoolean("Arm Limit Switch", g_arm.getLimitSwitchState());
  frc::SmartDashboard::PutBoolean("Front Intake Up", g_frontIntake.up());
  frc::SmartDashboard::PutBoolean("Front intake down", g_frontIntake.down());
  frc::SmartDashboard::PutNumber("X", g_drivetrain.getPose().X().to<double>());
  frc::SmartDashboard::PutNumber("Y", g_drivetrain.getPose().Y().to<double>());
  frc::SmartDashboard::PutBoolean("Feedforward Enabled", usingFeedForward);
  frc::SmartDashboard::PutBoolean("Jaws Closed", g_frontIntake.isClosed());
  //frc::SmartDashboard::PutBoolean("On Ramp", )
  //std::cout << g_frontIntake.down() << std::endl;
}

void cb::Robot::RobotInit() {
  std::cout << "Vader initializing\n";

  g_arm.resetPosition();
  g_arm.toggleArmBase();

  addAutoModeOptions();
  std::thread cameraThread(runCamera);
  cameraThread.detach();
}

void cb::Robot::RobotPeriodic() {
  updateSmartDashboardData();
  frc2::CommandScheduler::GetInstance().Run();
}

void cb::Robot::AutonomousInit() {
  isTeleop = false;
  m_autoCommand = getSelectedAutoCommand();

  if (m_autoCommand != nullptr) {
    m_autoCommand->Schedule();
  }
}

void cb::Robot::AutonomousPeriodic() {}

void cb::Robot::AutonomousExit() {
  if (m_autoCommand != nullptr) {
    m_autoCommand->Cancel();
  }
}

void cb::Robot::TeleopInit() {
  configureButtonBindings(); //map buttons
  g_drivetrain.setMotorMode(NeutralMode::Coast);
  isTeleop = true;
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
