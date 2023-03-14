#ifndef CONSTANTS
#define CONSTANTS

#include <units/acceleration.h>
#include <units/angle.h>
#include <units/length.h>
#include <units/velocity.h>
#include <units/voltage.h>

namespace cb {
    inline bool isTeleop = false;

    inline bool usingFeedForward = false;
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

    inline constexpr int FRONT_INTAKE_TALON_FX_ID = 12;
    inline constexpr int FRONT_INTAKE_TALON_SRX_ID = 15;

    inline constexpr int PCM_ID = 14;
    
    //Arm intake solenoid ID
    inline constexpr int SOLENOID_CHANNEL = 7;

    //double solenoid IDs on front intake
    inline constexpr int DOUBLE_SOLENOID_FORWARD_CHANNEL_ID = 6;
    inline constexpr int DOUBLE_SOLENOID_REVERSE_CHANNEL_ID = 5;

    //limit switch channels on front intake
    inline constexpr int UPPER_LIMIT_SWITCH_CHANNEL = 1;
    inline constexpr int LOWER_LIMIT_SWITCH_CHANNEL = 2;

    //limb motor ID
    inline constexpr int LIMB_ID = 10;

    inline constexpr int ARM_INTAKE_ID = 13;

    inline constexpr int LIMIT_SWITCH_CHANNEL_ID = 0;

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
    inline constexpr double maxArmVoltage = 0.4;

    inline constexpr double maxFeedForward = 0.2;

    inline constexpr double maxArmIntakePower = 0.80;

    inline constexpr double frontIntakePower =  0.75;
    inline constexpr double frontOuttakePower = 0.3;
    inline constexpr double frontIntakeDirPower = 0.14;

    inline constexpr double frontIntakeDownPos = 0;
    inline constexpr double frontIntakeUpPos = 33000;

    //arm auto constants
    inline constexpr double autoArmVoltage = 0.65;
    inline constexpr double armIntakeCubeSetpoint = -95000;
    inline constexpr double armIntakeConeSetpoint = -88000;
    
    inline constexpr units::volt_t toRampVoltage = 2.5_V;
    inline constexpr units::volt_t onRampVoltage = 1.25_V;

    //roll at which we are sure the robot is on the ramp
    inline constexpr double forwardRampRollThreshold = 10;

    inline constexpr units::volt_t turnRobotVolts = 1.75_V;

    //Feedforward robot characterization data
    inline constexpr units::volt_t ksDrivetrain = 0.24537_V;
    inline constexpr auto kvDrivetrain = 0.74916 * 1_V * 1_s / 1_m; 
    inline constexpr auto kaDrivetrain = 0.37692 * 1_V * 1_s * 1_s / 1_m;

    //PID values for forward drivetrain commands
    inline constexpr double kPDrivetrain = 0.001; //previously 1.0782
    inline constexpr double kIDrivetrain = 0.00003;
    inline constexpr double kDDrivetrain = 0.0; //previously 0.43708

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

    //Arm constants
    inline constexpr double kArmGearReduction = 176.8;
    inline constexpr double fullRotation = 312875;
}

#endif