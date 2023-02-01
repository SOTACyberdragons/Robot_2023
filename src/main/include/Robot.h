// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/Command.h>

#include <frc/smartdashboard/SendableChooser.h>

#include "RobotContainer.h"

//commands not included in robot container
#include "command_headers/DifferentialDriveWithJoysticks.h"
#include "command_headers/auto/DriveForward.h"

class Robot : public frc::TimedRobot {
public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  void SimulationInit() override;
  void SimulationPeriodic() override;
private:
  
};
