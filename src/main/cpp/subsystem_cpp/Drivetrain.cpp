#include "subsystem_headers/Drivetrain.h"

void cb::Drivetrain::Periodic() {
    // static double lastRoll = m_gyro.GetRoll();
    // std::cout << m_gyro.GetRoll() - lastRoll << std::endl;
    // lastRoll = m_gyro.GetRoll();
    //std::cout << getWheelSpeeds().right.to<double>() << std::endl;

    m_odometry.Update(getHeading(), units::meter_t(getLeftDistance()), units::meter_t(getRightDistance()));
}

frc::Rotation2d cb::Drivetrain::getHeading() {
    double angle = m_gyro.GetYaw();
    double newAngle = remainder(angle, 360); //absolutely no reason to have const boolean for making it positive/negative
    return units::radian_t(newAngle * (pi/180)); //return newAngle in radians
}

frc::Pose2d cb::Drivetrain::getPose() {
    return m_odometry.GetPose();
}

frc::DifferentialDriveWheelSpeeds cb::Drivetrain::getWheelSpeeds() {
    using units::velocity::meters_per_second;
    return 
    { 
        units::meters_per_second_t(m_leftMaster.GetSelectedSensorVelocity() * kEncoderDistancePerPulse),
        units::meters_per_second_t(m_rightMaster.GetSelectedSensorVelocity() * kEncoderDistancePerPulse) 
    };
}

double cb::Drivetrain::getWheelRPM() {
    return (60 / ((2 * pi) * kWheelRadiusMeters))
                * (m_leftMaster.GetSelectedSensorVelocity() * kEncoderDistancePerPulse);
}

void cb::Drivetrain::resetEncoders() {
    m_leftMaster.SetSelectedSensorPosition(0, PID_LOOP_IDX, TIMEOUT_MS);
    m_rightMaster.SetSelectedSensorPosition(0, PID_LOOP_IDX, TIMEOUT_MS);
}

double cb::Drivetrain::getLeftEncoder() {
    return m_leftMaster.GetSelectedSensorPosition();
}

double cb::Drivetrain::getRightEncoder() {
    return m_rightMaster.GetSelectedSensorPosition();
}

bool cb::Drivetrain::leftEncoderOutOfPhase() {
    return m_faults.SensorOutOfPhase;
}

units::meter_t cb::Drivetrain::getLeftDistance() {
    return static_cast<units::meter_t>(m_leftMaster.GetSelectedSensorPosition() * kEncoderDistancePerPulse);
}

units::meter_t cb::Drivetrain::getRightDistance() {
    return static_cast<units::meter_t>(m_rightMaster.GetSelectedSensorPosition() * kEncoderDistancePerPulse);
}

const WPI_Pigeon2& cb::Drivetrain::getGyro() const {
    return m_gyro;
}

void cb::Drivetrain::resetOdometry(frc::Pose2d pose) {
    resetEncoders();
    
    m_odometry.ResetPosition(getHeading(), 0.0_m, 0.0_m, pose);
}

void cb::Drivetrain::resetPosition() {
    m_odometry.ResetPosition(frc::Rotation2d(0.0, 0.0), 0.0_m, 0.0_m, 
    frc::Pose2d(0.0_m, 0.0_m, frc::Rotation2d(0.0, 0.0)));
}

void cb::Drivetrain::arcadeDrive(double fwd, double rot) {
    m_drive.ArcadeDrive(fwd, rot);
}

void cb::Drivetrain::tankDriveVolts(units::volt_t leftVolts, units::volt_t rightVolts) {
    m_leftMaster.SetVoltage(leftVolts);
    m_rightMaster.SetVoltage(rightVolts);
    m_drive.Feed();
}

double cb::Drivetrain::getAngle() {
    double xyz_dps[3];
    m_gyro.GetRawGyro(xyz_dps);
    return m_gyro.GetYaw();
}

void cb::Drivetrain::setAngle(double angle) {
    double distance = (m_leftMaster.GetSelectedSensorPosition(0) + m_rightMaster.GetSelectedSensorPosition(0)) / 2;
    double totalAngle = angle + getAngle();
    m_rightMaster.Set(
        ControlMode::PercentOutput, distance, DemandType::DemandType_ArbitraryFeedForward, -totalAngle
    );
}

void cb::Drivetrain::setDistance(double distance) {
    double distanceTicks = distance / kEncoderDistancePerPulse;
    double totalDistance = 
    ((m_leftMaster.GetSelectedSensorPosition() + m_rightMaster.GetSelectedSensorPosition()) / 2) + distanceTicks;
    double angle = getAngle();
    m_rightMaster.Set(ControlMode::MotionMagic, totalDistance, DemandType::DemandType_AuxPID, angle);
}

void cb::Drivetrain::resetDistance() {
    m_leftMaster.SetSelectedSensorPosition(0);
    m_leftSlave.SetSelectedSensorPosition(0);
    m_rightMaster.SetSelectedSensorPosition(0);
    m_rightSlave.SetSelectedSensorPosition(0);
}

void cb::Drivetrain::resetTalons() {
    m_leftMaster.ConfigFactoryDefault();
    m_leftSlave.ConfigFactoryDefault();
    m_rightMaster.ConfigFactoryDefault();
    m_rightSlave.ConfigFactoryDefault();

    m_leftSlave.Follow(m_leftMaster);
    m_rightSlave.Follow(m_rightMaster);

    m_leftMaster.SetSensorPhase(false);
    m_rightMaster.SetSensorPhase(false);

    m_leftMaster.SetSelectedSensorPosition(0);
    m_leftSlave.SetSelectedSensorPosition(0);
    m_rightMaster.SetSelectedSensorPosition(0);
    m_rightSlave.SetSelectedSensorPosition(0);

    m_leftMaster.SetInverted(true);
    m_leftSlave.SetInverted(true);
    m_rightMaster.SetInverted(false);
    m_rightSlave.SetInverted(false);

    m_leftMaster.SetNeutralMode(NeutralMode::Coast);
    m_leftSlave.SetNeutralMode(NeutralMode::Coast);
    m_rightMaster.SetNeutralMode(NeutralMode::Coast);
    m_rightSlave.SetNeutralMode(NeutralMode::Coast);
}

double cb::Drivetrain::getTurnRate() {
    double xyz_dps[3];
    m_gyro.GetRawGyro(xyz_dps);
    double currentAngularRate = xyz_dps[2];
    return currentAngularRate;
}

cb::Drivetrain::Drivetrain() 
    : m_odometry { getHeading(), 0_m, 0_m, getPose() }, m_drive { m_leftMaster, m_rightMaster }
{
    resetTalons();
}