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

    //Talon IDs 
    inline constexpr int LEFT_MASTER_ID = 5;
    inline constexpr int LEFT_SLAVE_ID = 4;
    inline constexpr int RIGHT_MASTER_ID = 6;
    inline constexpr int RIGHT_SLAVE_ID = 3;

    //shooter motors
    inline constexpr int LEFT_SHOOTER_MOTOR_ID = 4;
    inline constexpr int RIGHT_SHOOTER_MOTOR_ID = 5;

    //robot intake
    inline constexpr int INTAKE_MOTOR_ID = 6;
    inline constexpr int FEEDER_MOTOR_ID = 7;

    // DIO
    inline constexpr int FEEDER_BREAKBEAM_ID = 1;

    //Solenoid arm ID
    inline constexpr int SOLENOID_ID = 11;

    //limb motor ID
    inline constexpr int LIMB_ID = 10;

    //pigeon ID
    inline constexpr int PIGEON_ID = 8;

    //Talon FX configuration constants
    inline constexpr int kTimeoutMs = 30;
    inline constexpr int kPIDLoopIdx = 0;
    inline constexpr double kEncoderMaxSpeed = 33000;

    //Max speed and acceleration for drivetrain
    //inline constexpr units::meters_per_second_t kMaxSpeed = 2_mps;
    //inline constexpr units::meters_per_second_squared_t kMaxAcceleration = 1_mps_sq;

    //manual arm moving constants
    inline constexpr double maxArmVoltage = 2.5;
    inline constexpr double maxFeedForward = 1.5;

    //voltage used to rotate the arm
    inline constexpr units::volt_t autoArmVoltage = 5_V;

    inline constexpr units::volt_t toRampVoltage = 4_V;
    inline constexpr units::volt_t onRampVoltage = 1_V;

    //Feedforward robot characterization data
    inline constexpr units::volt_t ksDrivetrain = 0.24537_V;
    inline constexpr auto kvDrivetrain = 0.74916 * 1_V * 1_s / 1_m; 
    inline constexpr auto kaDrivetrain = 0.37692 * 1_V * 1_s * 1_s / 1_m;

    //PID values for forward drivetrain commands
    inline constexpr double kPDrivetrain = 0.001; //previously 1.0782
    inline constexpr double kIDrivetrain = 0.00003;
    inline constexpr double kDDrivetrain = 0.0; //previously 0.43708

    //PID values that are tunable from smartdashboard
    inline double sKPDrivetrain = 0.001;
    inline double sKIDrivetrain = 0.00003;
    inline double sKDDrivetrain = 0.0;

    //Angular robot characterization data
    inline constexpr double ksAngular = 0.59266;
    inline constexpr double kvAngular = 0.87714;
    inline constexpr double kaAngular = 0.38704;

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
    inline double kMaxDriveSpeed = 0.85;
    inline double kMaxTurnSpeed = 0.65;

    // Drivetrain wheel constants
    inline constexpr int kEncoderCPR = 2048;
    inline constexpr double kWheelDiameterMeters = 0.152;
    inline constexpr double kWheelRadiusMeters = kWheelDiameterMeters / 2;
    inline constexpr double kGearRation = 7.6363;
    inline constexpr double kEncoderDistancePerPulse =
            ((kWheelDiameterMeters * pi) / static_cast<double>(kEncoderCPR)) / kGearRation;
}

#endif