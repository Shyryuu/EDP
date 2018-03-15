
cmake_minimum_required(VERSION 2.8.12.2)
project ( Mendelbrot )
find_package (OpenCV REQUIRED)

set (CMAKE_CXX_COMPILER mpic++)

file (GLOB_RECURSE INCLUDES "include/*.h")
file (GLOB_RECURSE SOURCES "src/*.cxx")

include_directories( ${OpenCV_INCLUDE_DIRS} ${INCLUDES})

add_executable (main ${SOURCES})

target_link_libraries (main ${OpenCV_LIBS})