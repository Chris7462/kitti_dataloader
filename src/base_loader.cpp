#include <algorithm>
#include <fstream>
#include <filesystem>

#include "kitti_dataloader/base_loader.hpp"


namespace fs = std::filesystem;

BaseLoader::BaseLoader()
: current_index_(0),
  total_count_(0)
{
}

void BaseLoader::loadDataPaths(const std::string & folder, const std::string & extension)
{
  if (!fs::exists(folder)) {
    throw std::runtime_error("Data folder does not exist: " + folder);
  }

  data_paths_.clear();
  for (auto const & entry : fs::directory_iterator(folder)) {
    if (entry.path().extension() == extension) {
      data_paths_.push_back(entry.path().string());
    }
  }
  std::sort(data_paths_.begin(), data_paths_.end());
}

void BaseLoader::loadTimestamps(const std::string & filepath)
{
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open timestamps file: " + filepath);
  }

  std::string line;
  while (std::getline(file, line)) {
    timestamps_.push_back(line);
  }
}

bool BaseLoader::hasNext() const
{
  return current_index_ < total_count_;
}
