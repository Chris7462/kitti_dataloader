#pragma once

#include <array>
#include <string>
#include <vector>


struct CalibrationPacket
{
  std::array<double, 9> K;
  std::vector<double> D;
  std::array<double, 2> S_rect;
  std::array<double, 9> R_rect;
  std::array<double, 12> P_rect;
};

class CalibrationLoader
{
public:
  explicit CalibrationLoader(const std::string & calib_path);
  std::vector<double> parseDoublesFromLine(const std::string & line);
  std::array<CalibrationPacket, 4> camera_;
};
