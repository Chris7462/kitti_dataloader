#include "kitti_dataloader/camera_loader.hpp"


CameraLoader::CameraLoader(const std::string& camera_path)
{
  loadDataPaths(camera_path + "/data", ".png");
  loadTimestamps(camera_path + "/timestamps.txt");

  if (data_paths_.size() != timestamps_.size()) {
    throw std::runtime_error("Image count and timestamp count mismatch in " + camera_path);
  }

  current_index_ = 0;
  total_count_ = data_paths_.size();
}

std::shared_ptr<DataPacket> CameraLoader::next()
{
  if (!hasNext()) {
    throw std::out_of_range("No more frames in stream");
  }

  auto pkt = std::make_shared<CameraPacket>();

  pkt->image = cv::imread(data_paths_[current_index_], cv::IMREAD_COLOR);
  if (pkt->image.empty()) {
    throw std::runtime_error("Failed to read image file: " + data_paths_[current_index_]);
  }

  pkt->timestamp = timestamps_[current_index_];
  ++current_index_;

  return pkt;
}
