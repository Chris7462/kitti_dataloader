cmake_minimum_required(VERSION 3.8)
project(kitti_dataloader VERSION 1.0.0)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(OpenCV REQUIRED)

# Define the library target
add_library(kitti_dataloader STATIC
  src/base_loader.cpp
  src/camera_loader.cpp
  src/oxts_loader.cpp
  src/velodyne_loader.cpp
  src/calibration_loader.cpp)

# Specify include directories for the target
target_include_directories(kitti_dataloader PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${OpenCV_INCLUDE_DIRS})

# Link OpenCV libraries to the target
target_link_libraries(kitti_dataloader PUBLIC
  ${OpenCV_LIBS})

target_compile_features(kitti_dataloader PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17

# Optionally install the library
install(TARGETS kitti_dataloader
  EXPORT export_${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

# Install header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/kitti_dataloader
  DESTINATION include
)

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(OpenCV)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)

  ament_add_gtest(all_loader_test
    test/all_loader_test.cpp
    src/base_loader.cpp
    src/camera_loader.cpp
    src/oxts_loader.cpp
    src/velodyne_loader.cpp
    src/calibration_loader.cpp)

  target_include_directories(all_loader_test PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${OpenCV_INCLUDE_DIRS})

  target_link_libraries(all_loader_test
    gtest_main
    ${OpenCV_LIBS})

endif()

ament_package()
