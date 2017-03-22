cmake_minimum_required(VERSION 2.8.12)
project(sandboxed_ros_controller)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(CATKIN_DEPENDS roscpp std_msgs)

include_directories(${catkin_INCLUDE_DIRS})
link_libraries(${catkin_LIBRARIES})

add_executable(sandboxed_ros_controller_node src/sandboxed_ros_controller_node.cpp)

install(TARGETS sandboxed_ros_controller_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

