#include <fstream>

#include "kitti_dataloader/velodyne_loader.hpp"


VelodyneLoader::VelodyneLoader(const std::string & velodyne_path)
{
  loadDataPaths(velodyne_path + "/data", ".bin");
  loadTimestamps(velodyne_path + "/timestamps.txt");

  if (data_paths_.size() != timestamps_.size()) {
    throw std::runtime_error("Mismatch between Velodyne .bin files and timestamps.");
  }

  current_index_ = 0;
  total_count_ = data_paths_.size();
}

std::shared_ptr<DataPacket> VelodyneLoader::next()
{
  if (!hasNext()) {
    throw std::out_of_range("No more Velodyne frames");
  }

  const std::string & path = data_paths_[current_index_];
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Failed to open Velodyne file: " + path);
  }

  auto cloud = std::make_shared<VelodynePacket>();

  std::array<float, 4> point;
  while (file.read(reinterpret_cast<char *>(point.data()), sizeof(float) * 4)) {
    cloud->points.push_back(point);
  }

  cloud->timestamp = timestamps_[current_index_];
  ++current_index_;

  return cloud;
}
