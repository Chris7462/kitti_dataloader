#pragma once

#include <opencv2/opencv.hpp>

#include "kitti_dataloader/base_loader.hpp"


struct CameraPacket : public DataPacket
{
  cv::Mat image;
};

class CameraLoader : public BaseLoader
{
public:
  explicit CameraLoader(const std::string & camera_path);
  std::shared_ptr<DataPacket> next() override;
};
