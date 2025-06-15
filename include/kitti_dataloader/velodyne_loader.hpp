#pragma once

#include <array>

#include "kitti_dataloader/base_loader.hpp"


struct VelodynePacket : public DataPacket
{
  std::vector<std::array<float, 4>> points;
};

class VelodyneLoader : public BaseLoader
{
public:
  explicit VelodyneLoader(const std::string & velodyne_path);
  std::shared_ptr<DataPacket> next() override;
};
