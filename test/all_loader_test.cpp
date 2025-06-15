#include <gtest/gtest.h>

#include "kitti_dataloader/camera_loader.hpp"
#include "kitti_dataloader/oxts_loader.hpp"
#include "kitti_dataloader/velodyne_loader.hpp"


class CameraTest : public ::testing::Test
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
  }

  void TearDown() override
  {
  }

  std::vector<std::shared_ptr<BaseLoader>> loaders;
};

TEST_F(CameraTest, Constructor_TC1)
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
}
