cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(main)

find_package(PCL 1.10 REQUIRED)
find_package(OpenCV REQUIRED)

set(path ./source)

file(GLOB src "${path}/*.cpp")

include_directories(${PCL_INCLUDE_DIRS})
include_directories (${CMAKE_SOURCE_DIR}/entete)
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable (main ${src})
target_link_libraries (main ${PCL_LIBRARIES})


