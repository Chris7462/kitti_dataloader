#pragma once

#include "kitti_dataloader/base_loader.hpp"


struct OxtsPacket : public DataPacket
{
  std::vector<double> values;
};

class OxtsLoader : public BaseLoader
{
public:
  OxtsLoader(const std::string & oxts_path);
  std::shared_ptr<DataPacket> next() override;
};
