#include <fstream>
#include <regex>
#include <sstream>

#include "kitti_dataloader/calibration_loader.hpp"


CalibrationLoader::CalibrationLoader(const std::string & calib_path)
{
  std::ifstream file(calib_path);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open calibration file: " + calib_path);
  }

  std::string line;
  std::regex regex_key(R"((K|D|S_rect|R_rect|P_rect)_(\d+))");

  while (std::getline(file, line)) {
    std::smatch match;
    if (std::regex_search(line, match, regex_key)) {
      std::string type = match[1];
      int cam_id = std::stoi(match[2]);
      if (cam_id < 0 || cam_id >= 4) {
        continue;
      }

      std::vector<double> values = parseDoublesFromLine(line);
      if (type == "K" && values.size() == 9) {
        std::copy(values.begin(), values.end(), camera_[cam_id].K.begin());
      } else if (type == "D") {
        camera_[cam_id].D = values;
      } else if (type == "S_rect" && values.size() == 2) {
        std::copy(values.begin(), values.end(), camera_[cam_id].S_rect.begin());
      } else if (type == "R_rect" && values.size() == 9) {
        std::copy(values.begin(), values.end(), camera_[cam_id].R_rect.begin());
      } else if (type == "P_rect" && values.size() == 12) {
        std::copy(values.begin(), values.end(), camera_[cam_id].P_rect.begin());
      }
    }
  }
}

std::vector<double> CalibrationLoader::parseDoublesFromLine(const std::string & line)
{
  std::istringstream iss(line);
  std::string key;
  iss >> key;
  std::vector<double> values;
  double val;
  while (iss >> val) {
    values.push_back(val);
  }

  return values;
}
