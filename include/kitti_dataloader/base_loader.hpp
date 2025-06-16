#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>


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

  // This function is only used for testing.
  inline size_t get_total_count() {return total_count_;}

protected:
  void loadDataPaths(const std::string & folder, const std::string & extension);
  void loadTimestamps(const std::string & file_path);

  std::vector<std::string> data_paths_;
  std::vector<std::string> timestamps_;
  size_t current_index_;
  size_t total_count_;
};
