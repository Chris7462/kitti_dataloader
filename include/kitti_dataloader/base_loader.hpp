#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>


struct DataPacket
{
  std::string timestamp;
  virtual ~DataPacket() = default;
};

class BaseLoader
{
public:
  BaseLoader();
  virtual ~BaseLoader() = default;

  virtual std::shared_ptr<DataPacket> next() = 0;
  bool hasNext() const;

protected:
  void loadDataPaths(const std::string & folder,
    const std::string & extension);
  void loadTimestamps(const std::string & filepath);

  std::vector<std::string> data_paths_;
  std::vector<std::string> timestamps_;
  size_t current_index_;
  size_t total_count_;
};
