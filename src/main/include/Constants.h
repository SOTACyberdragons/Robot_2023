#ifndef CONSTANTS
#define CONSTANTS

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
    inline constexpr int LEFT_MASTER_ID = 1;
    inline constexpr int LEFT_SLAVE_ID = 0;
    inline constexpr int RIGHT_MASTER_ID = 3;
    inline constexpr int RIGHT_SLAVE_ID = 2;

    //shooter motors
    inline constexpr int LEFT_SHOOTER_MOTOR_ID = 4;
    inline constexpr int RIGHT_SHOOTER_MOTOR_ID = 5;

    // robotintake
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

    //pigeon ID
    inline constexpr int PIGEON_IMU_ID = 14;

    //Talon FX configuration constants
    inline constexpr int kTimeoutMs = 30;
    inline constexpr int kPIDLoopIdx = 0;
    inline constexpr double kEncoderMaxSpeed = 33000;

    //TODO Forward robot characterization data
    inline constexpr double ksDrivetrain = 0.77132;
    inline constexpr double kvDrivetrain = 5.0013;
    inline constexpr double kaDrivetrain = 2.0347;

    //TODO PID values for forward drivetrain commands
    inline constexpr double kPDrivetrain = 0.12991;
    inline constexpr double kIDrivetrain = 0.0;
    inline constexpr double kDDrivetrain = 0.013708;

    //TODO Angular robot characterization data
    inline constexpr double ksAngular = 0.7918;
    inline constexpr double kvAngular = 0.0022871;
    inline constexpr double kaAngular = 0.000113;

     //TODO PID values for angular drivetrain commands
    inline constexpr double kPAngular = 0.048135;
    inline constexpr double kIAngular = 0.0;
    inline constexpr double kDAngular = 0.00082831;

    inline constexpr double kTrackwidthMeters = 0.25732;

    //math stuff
    inline constexpr double pi = 3.14159265358979323846;

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