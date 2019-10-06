# CMakeList.txt : CMake project for rogue, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#add_subdirectory(util)
add_subdirectory(core)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)
add_executable (handmade "main.cpp")

include_directories(glad)
include_directories(glad/include)
include_directories(glfw)
include_directories(glfw/include)

target_link_libraries(handmade glad)
target_link_libraries(handmade glfw)

target_include_directories(handmade PUBLIC glad)
target_include_directories(handmade PUBLIC glfw)

include_directories(core)
target_link_libraries(handmade core)
target_include_directories(handmade PUBLIC core)
