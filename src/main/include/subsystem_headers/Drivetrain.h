#ifndef DRIVE_TRAIN
#define DRIVE_TRAIN

#include <iostream>

#include <frc2/command/SubsystemBase.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveWheelSpeeds.h>
#include <frc/drive/DifferentialDrive.h>

#include <ctre/phoenix/motorcontrol/can/WPI_TalonFX.h>
#include <ctre/phoenix/motorcontrol/Faults.h>
#include <ctre/phoenix/sensors/WPI_PigeonIMU.h>

#include "subsystem_headers/Drivetrain.h"
#include "Constants.h"

using ctre::phoenix::motorcontrol::can::WPI_TalonFX;
using ctre::phoenix::motorcontrol::Faults;
using ctre::phoenix::sensors::WPI_PigeonIMU;
using ctre::phoenix::motorcontrol::NeutralMode;
using ctre::phoenix::motorcontrol::ControlMode;
using ctre::phoenix::motorcontrol::DemandType;

namespace cb {
    inline const frc::DifferentialDriveKinematics kDriveKinematics(kTrackwidthMeters);

    class Drivetrain : public frc2::SubsystemBase {
    private:
        WPI_TalonFX m_leftMaster { cb::LEFT_MASTER_ID };
        WPI_TalonFX m_leftSlave { cb::LEFT_SLAVE_ID };
        WPI_TalonFX m_rightMaster { cb::RIGHT_MASTER_ID };
        WPI_TalonFX m_rightSlave { cb::RIGHT_SLAVE_ID };

        Faults m_faults;

        const WPI_PigeonIMU m_gyro { cb::PIGEON_IMU_ID };

        frc::DifferentialDrive m_drive;
        frc::DifferentialDriveOdometry m_odometry;

        virtual void Periodic() override;
    public:
        frc::DifferentialDriveWheelSpeeds getWheelSpeeds();

        double getWheelRPM(); 

        void resetEncoders();

        double getLeftEncoder(); 
        double getRightEncoder(); 

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