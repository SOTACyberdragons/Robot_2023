#include "subsystem_headers/VisionProcessor.h"

std::vector<cb::Target> cb::VisionProcessor::findTargets(cv::Mat& mat) {
  std::vector<Target> targets;

  cv::Mat grayMat, edges;

  //Convert mat to grayscale. The grayscale image is outputted to grayMat
  cv::cvtColor(mat, grayMat, cv::COLOR_BGR2GRAY);

  //get edge shapes within grayscale image
  cv::Canny(grayMat, edges, 50, 200);

  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(edges, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

  for (size_t i = 0; i < contours.size(); i++) {
    // Approximate the contour to a polygon
    std::vector<cv::Point> approx;
    cv::approxPolyDP(contours[i], approx, 0.02 * cv::arcLength(contours[i], true), true);

    //check number of vertices
    if (approx.size() == 4) {
      targets.push_back(Target::CUBE);
    } else if (approx.size() == 3) {
      targets.push_back(Target::CONE);
    } 
  }

  return targets;
};  

void cb::VisionProcessor::Periodic() {
    m_runningCamera = true;

    cs::UsbCamera camera = frc::CameraServer::StartAutomaticCapture();
    camera.SetResolution(640, 480);

    // Get a CvSink. This will capture Mats from the Camera
    cs::CvSink cvSink = frc::CameraServer::GetVideo();

    // Setup a CvSource. This will send images back to the Dashboard
    cs::CvSource outputStream =
        frc::CameraServer::PutVideo("Rectangle", 640, 480);
    
    cv::Mat mat, grey;

    int count = 0;

    while (m_runningCamera) {
      if (cvSink.GrabFrame(mat) == 0) {
        outputStream.NotifyError(cvSink.GetError());
        continue;
      }

      m_coneProcessor.Process(mat);
      std::vector<cv::KeyPoint>* blobs = m_coneProcessor.GetFindBlobsOutput();
      if (m_coneProcessor.GetFindBlobsOutput()->size() > 0) { //if we have detected shapes
        std::cout << "Shapes detected!\n";
        std::vector<std::vector<cv::Point>> contours;
        for (const cv::KeyPoint& blob : *blobs) { //convert the blobs to contours
          contours.push_back(std::vector<cv::Point>{blob.pt});
        }
        cv::Rect r = cv::boundingRect(contours);
        m_centerX = r.x + (r.width / 2);
      }
    }
}

int cb::VisionProcessor::getCenterX() const noexcept {
  return m_centerX;
}

void cb::VisionProcessor::stop() {
    m_runningCamera = false;
}