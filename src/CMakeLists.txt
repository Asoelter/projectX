# CMakeList.txt : CMake project for rogue, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)
add_executable (handmade "main.cpp")

target_link_libraries(handmade ${X11_LIBRARIES})
