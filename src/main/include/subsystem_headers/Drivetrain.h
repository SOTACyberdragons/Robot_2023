#ifndef DRIVE_TRAIN
#define DRIVE_TRAIN

#include <iostream>
#include <math.h>

#include <frc2/command/SubsystemBase.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveWheelSpeeds.h>
#include <frc/drive/DifferentialDrive.h>

#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <ctre/phoenix/sensors/Pigeon2.h>
#include <ctre/phoenix/motorcontrol/Faults.h>
#include <ctre/phoenix/sensors/WPI_Pigeon2.h>
#include "subsystem_headers/Drivetrain.h"
#include "Constants.h"

using ctre::phoenix::motorcontrol::can::WPI_TalonFX;
using ctre::phoenix::motorcontrol::Faults;
using ctre::phoenix::sensors::WPI_Pigeon2;
using ctre::phoenix::motorcontrol::NeutralMode;
using ctre::phoenix::motorcontrol::ControlMode;
using ctre::phoenix::motorcontrol::DemandType;

namespace cb {
    inline const frc::DifferentialDriveKinematics kDriveKinematics { kTrackwidthMeters };

    class Drivetrain : public frc2::SubsystemBase {
    private:
        WPI_TalonFX m_leftMaster { LEFT_MASTER_ID };
        WPI_TalonFX m_leftSlave { LEFT_SLAVE_ID };
        WPI_TalonFX m_rightMaster { RIGHT_MASTER_ID };
        WPI_TalonFX m_rightSlave { RIGHT_SLAVE_ID };

        Faults m_faults;

        WPI_Pigeon2 m_gyro { PIGEON_ID };

        frc::DifferentialDrive m_drive;
        frc::DifferentialDriveOdometry m_odometry;

        virtual void Periodic() override;
    public:
        //returns negative velocity for going forward, positive velocity for going backward
        frc::DifferentialDriveWheelSpeeds getWheelSpeeds();

        double getWheelRPM(); 

        void resetEncoders();

        double getLeftEncoder(); 
        double getRightEncoder(); 

        const WPI_Pigeon2& getGyro() const;

        bool leftEncoderOutOfPhase();

        units::meter_t getLeftDistance();
        units::meter_t getRightDistance();

        double getTurnRate();

        frc::Rotation2d getHeading();
        frc::Pose2d getPose();

        void resetOdometry(frc::Pose2d pose);
        void resetPosition();

        void arcadeDrive(double fwd, double rot);

        void tankDriveVolts(units::volt_t leftVolts, units::volt_t rightVolts); 

        double getAngle();

        void setAngle(double angle);

        void setDistance(double distance);

        void resetDistance();
        void resetTalons();

        //copy constructor
        Drivetrain(const Drivetrain& drivetrain);
        //constructor
        Drivetrain(); 
    };

    //subsystem instance
    inline Drivetrain g_drivetrain;
}

#endif