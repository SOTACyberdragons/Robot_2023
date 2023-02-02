#ifndef DRIVE_FORWARD
#define DRIVE_FORWARD

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include <units/length.h>

#include "subsystem_headers/Drivetrain.h"

namespace cb {
    class DriveForward : 
    public frc2::CommandHelper<frc2::CommandBase, DriveForward> {
    private:
        Drivetrain& m_drive;

        units::meter_t m_meters = 0_m;
        
        double m_power = 0;

        void Initialize() override;
        void Execute() override;
        bool IsFinished() override;
    public:
        //g_drivetrain from robotcontainer must be passed in
        DriveForward(Drivetrain& drivetrain, units::meter_t meters); 
    };
}

#endif