#ifndef CONSTANTS
#define CONSTANTS

#include <units/acceleration.h>
#include <units/angle.h>
#include <units/length.h>
#include <units/velocity.h>
#include <units/voltage.h>

namespace cb {
    /**
     * Talon SRX/ Victor SPX will supported multiple (cascaded) PID loops. For now we just want the
     * primary one.
     */
    inline constexpr int PID_LOOP_IDX = 0;

    /**
     * set to zero to skip waiting for confirmation, set to nonzero to wait and report to DS if
     * action fails.
     */
    inline constexpr int TIMEOUT_MS = 10;

    //talon IDs
    inline constexpr int LEFT_MASTER_ID = 0;
    inline constexpr int LEFT_SLAVE_ID = 1;
    inline constexpr int RIGHT_MASTER_ID = 3;
    inline constexpr int RIGHT_SLAVE_ID = 2;

    //shooter motors
    inline constexpr int LEFT_SHOOTER_MOTOR_ID = 4;
    inline constexpr int RIGHT_SHOOTER_MOTOR_ID = 5;

    //robot intake
    inline constexpr int INTAKE_MOTOR_ID = 6;
    inline constexpr int FEEDER_MOTOR_ID = 7;

    // climber
    inline constexpr int PRIMARY_ARM_MOTOR_ID = 9;
    inline constexpr int SECONDARY_ARM_MOTOR_ID = 8;
    inline constexpr int PRIMARY_PIVOT_MOTOR_ID = 10;
    inline constexpr int SECONDARY_PIVOT_MOTOR_ID = 11;

    // PCM
    inline constexpr int DOUBLE_SOLENOID_ZERO_ID = 0;
    inline constexpr int DOUBLE_SOLENOID_ONE_ID = 7;

    // DIO
    inline constexpr int FEEDER_BREAKBEAM_ID = 1;

    //Solenoid arm ID
    inline constexpr int SOLENOID_ID = 0;

    //limb motor ID
    inline constexpr int LIMB_ID = 4;

    //pigeon ID
    inline constexpr int PIGEON_IMU_ID = 14;

    //Talon FX configuration constants
    inline constexpr int kTimeoutMs = 30;
    inline constexpr int kPIDLoopIdx = 0;
    inline constexpr double kEncoderMaxSpeed = 33000;

    //Feedforward robot characterization data
    inline constexpr units::volt_t ksDrivetrain = 0.26443_V;
    inline constexpr auto kvDrivetrain = 0.41799 * 1_V * 1_s / 1_m; //previously 0.71799
    inline constexpr auto kaDrivetrain = 0.33937 * 1_V * 1_s * 1_s / 1_m;

    //Max speed and acceleration
    inline constexpr units::meters_per_second_t kMaxSpeed = 1_mps;
    inline constexpr units::meters_per_second_squared_t kMaxAcceleration = 1_mps_sq;

    //PID values for forward drivetrain commands
    inline constexpr double kPDrivetrain = 1.0782; //previously 1.0782
    inline constexpr double kIDrivetrain = 0.6;
    inline constexpr double kDDrivetrain = 0.6; //previously 0.43708

    //voltage used to rotate the arm
    inline constexpr units::volt_t armVoltage = 1_V;

    //TODO Angular robot characterization data
    inline constexpr double ksAngular = 0.7918;
    inline constexpr double kvAngular = 0.0022871;
    inline constexpr double kaAngular = 0.000113;

     //TODO PID values for angular drivetrain commands
    inline constexpr double kPAngular = 0.048135;
    inline constexpr double kIAngular = 0.0;
    inline constexpr double kDAngular = 0.00082831;

    /*The RamseteController constructor signature changed, 
    so we have to use these units instead of double. I have no idea
    what literals to use so I'm just converting them with
    these aliases*/
    using b_unit = units::unit_t<units::compound_unit<units::squared<units::radians>,
                           units::inverse<units::squared<units::meters>>>>;
    using zeta_unit = units::unit_t<units::inverse<units::radians>>;

    inline constexpr b_unit kRamseteB = 2 * b_unit(1); 
    inline constexpr zeta_unit kRamseteZeta = 0.7 * zeta_unit(1);

    inline constexpr units::meter_t kTrackwidthMeters = 0.25732_m;

    //pi
    inline constexpr double pi = 3.14159265358979323846;

    //camera resolution constants
    inline constexpr int cameraWidth = 640;
    inline constexpr int cameraHeight = 480;

    inline constexpr int cameraFocalLength = 20;

    //object size constants
    inline constexpr int coneWidth = 0;
    inline constexpr int coneHeight = 0;
    inline constexpr int cubeWidth = 0;
    inline constexpr int cubeHeight = 0;

    // XBox Controller Drivetrain Constants
    inline constexpr double kMaxDriveSpeed = 0.7;
    inline constexpr double kMaxTurnSpeed = 0.7;

    // Drivetrain wheel constants
    inline constexpr int kEncoderCPR = 2048;
    inline constexpr double kWheelDiameterMeters = 0.152;
    inline constexpr double kWheelRadiusMeters = kWheelDiameterMeters / 2;
    inline constexpr double kGearRation = 7.6363;
    inline constexpr double kEncoderDistancePerPulse =
            ((kWheelDiameterMeters * pi) / (double) kEncoderCPR) / kGearRation;
}

#endif