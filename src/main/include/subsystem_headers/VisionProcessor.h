#ifndef VISION_PROCESSOR
#define VISION_PROCESSOR

#include <iostream>

#include <frc2/command/SubsystemBase.h>

#include <cameraserver/CameraServer.h>
#include <frc/TimedRobot.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
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

        int getCenterX() const noexcept;

        Target getTarget() const noexcept;
    };
}

#endif