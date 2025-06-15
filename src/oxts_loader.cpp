#include <fstream>
#include <sstream>

#include "kitti_dataloader/oxts_loader.hpp"


OxtsLoader::OxtsLoader(const std::string& oxts_path)
{
  loadDataPaths(oxts_path + "/data", ".txt");
  loadTimestamps(oxts_path + "/timestamps.txt");

  if (data_paths_.size() != timestamps_.size()) {
    throw std::runtime_error("Mismatch between OXTS data and timestamps.");
  }

  current_index_ = 0;
  total_count_ = data_paths_.size();
}

std::shared_ptr<DataPacket> OxtsLoader::next()
{
  if (!hasNext()) {
    throw std::out_of_range("No more OXTS frames");
  }

  std::ifstream file(data_paths_[current_index_]);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open OXTS data file: " + data_paths_[current_index_]);
  }

  std::string line;
  std::getline(file, line);
  std::istringstream iss(line);

  auto data = std::make_shared<OxtsPacket>();
  double val;
  while (iss >> val) {
    data->values.push_back(val);
  }

  data->timestamp = timestamps_[current_index_];
  ++current_index_;

  return data;
}
