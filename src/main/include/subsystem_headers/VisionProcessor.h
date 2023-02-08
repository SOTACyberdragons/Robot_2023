#ifndef VISION_PROCESSOR
#define VISION_PROCESSOR

#include <iostream>

#include <frc2/command/SubsystemBase.h>
#include <frc/geometry/Rotation2d.h>

#include <units/length.h>
#include <units/angle.h>

#include <cameraserver/CameraServer.h>
#include <frc/TimedRobot.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include "Constants.h"
#include "ConePipeline.h"

namespace cb {
    enum class Target {
        CUBE,
        CONE,
        NO_TARGET
    };

    class VisionProcessor : public frc2::SubsystemBase {
    private:
        cs::UsbCamera m_camera;
        bool m_runningCamera = false;

        double m_centerX = 0;

        grip::ConePipeline m_coneProcessor;

        Target m_target = Target::NO_TARGET;

        std::vector<Target> findTargets(cv::Mat& mat);

        void Periodic() override;
    public:
        void stop();

        std::pair<units::meter_t, units::radian_t> getObjectPosition();

        int getCenterX() const noexcept;

        Target getTarget() const noexcept;
    };

    //inline VisionProcessor g_processor;
}

#endif