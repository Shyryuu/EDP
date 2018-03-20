
cmake_minimum_required(VERSION 2.8.12.2)
project ( EDP )
# find_package (OpenCV REQUIRED)

set (CMAKE_CXX_COMPILER mpic++)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file (GLOB_RECURSE SOURCES "src/*.cxx")

include_directories( ${OpenCV_INCLUDE_DIRS} include/)

add_executable (main ${SOURCES})

# target_link_libraries (main ${OpenCV_LIBS})