cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(sandboxed_ros_controller)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

ament_package()

include_directories(${rclcpp_INCLUDE_DIRS} ${std_msgs_INCLUDE_DIRS})
link_libraries(${rclcpp_LIBRARIES} ${std_msgs_LIBRARIES})

add_executable(sandboxed_ros_controller_node src/sandboxed_ros_controller_node.cpp)

install(TARGETS sandboxed_ros_controller_node
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

