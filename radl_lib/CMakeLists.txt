cmake_minimum_required(VERSION 2.8)

project(radl_lib)
catkin_package(LIBRARIES radl_lib)

add_library(radl_lib STATIC src/radl_lib.c)
target_include_directories(radl_lib PUBLIC include)

