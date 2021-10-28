cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(radl_lib)

find_package(ament_cmake REQUIRED)

add_library(${PROJECT_NAME} STATIC src/radl_lib.c)
target_include_directories(${PROJECT_NAME} 
  PUBLIC 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>")

ament_export_include_directories(include)
ament_export_targets(export_${PROJECT_NAME})
ament_export_libraries(${PROJECT_NAME})

ament_package()

install(DIRECTORY include/
  DESTINATION include)

install(TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)
