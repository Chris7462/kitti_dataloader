#include <gtest/gtest.h>

#include "kitti_dataloader/camera_loader.hpp"
#include "kitti_dataloader/oxts_loader.hpp"
#include "kitti_dataloader/velodyne_loader.hpp"
#include "kitti_dataloader/calibration_loader.hpp"


class AllLoaderTest : public ::testing::Test
{
public:
  void SetUp() override
  {
    loaders.push_back(std::make_shared<CameraLoader>(
      "/data/kitti/raw/2011_09_29/2011_09_29_drive_0071_sync/image_00"));
    loaders.push_back(std::make_shared<OxtsLoader>(
      "/data/kitti/raw/2011_09_29/2011_09_29_drive_0071_sync/oxts"));
    loaders.push_back(std::make_shared<VelodyneLoader>(
      "/data/kitti/raw/2011_09_29/2011_09_29_drive_0071_sync/velodyne_points"));
    calib_loader = std::make_shared<CalibrationLoader>(
      "/data/kitti/raw/2011_09_29/calib_cam_to_cam.txt");
  }

  void TearDown() override
  {
  }

  std::vector<std::shared_ptr<BaseLoader>> loaders;
  std::shared_ptr<CalibrationLoader> calib_loader;
};

TEST_F(AllLoaderTest, Constructor_TC1)
{
  for (auto & loader : loaders) {
    EXPECT_EQ(loader->get_total_count(), 1059);
    while (loader->hasNext()) {
      auto pkt = loader->next();
      std::cout << "Timestamp: " << pkt->timestamp;

      if (auto frame = std::dynamic_pointer_cast<CameraPacket>(pkt)) {
        std::cout << "  Image size: " << frame->image.cols << "x" << frame->image.rows << std::endl;
      } else if (auto oxts = std::dynamic_pointer_cast<OxtsPacket>(pkt)) {
        std::cout << "  OXTS first value: " << oxts->values.front() << std::endl;
      } else if (auto lidar = std::dynamic_pointer_cast<VelodynePacket>(pkt)) {
        std::cout << "  LiDAR points: " << lidar->points.size() << std::endl;
      }
    }
  }

  for (int i = 0; i < 4; ++i) {
    auto & camera = calib_loader->camera_[i];
    std::cout << "K_0" << i << ": ";
    for (auto k : camera.K) {
      std::cout << k << " ";
    }
    std::cout << std::endl;

    std::cout << "D_0" << i << ": ";
    for (auto d : camera.D) {
      std::cout << d << " ";
    }
    std::cout << std::endl;

    std::cout << "S_rect_0" << i << ": ";
    for (auto s : camera.S_rect) {
      std::cout << s << " ";
    }
    std::cout << std::endl;

    std::cout << "R_rect_0" << i << ": ";
    for (auto r : camera.R_rect) {
      std::cout << r << " ";
    }
    std::cout << std::endl;

    std::cout << "P_rect_0" << i << ": ";
    for (auto p : camera.P_rect) {
      std::cout << p << " ";
    }
    std::cout << std::endl;
  }
}
