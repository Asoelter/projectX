# CMakeList.txt : CMake project for rogue, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#add_subdirectory(util)
add_subdirectory(core)
add_subdirectory(game)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)

if(WIN32)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../../../)
else()
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)
endif(WIN32)

add_executable (${PROJECT_NAME} "main.cpp")

include_directories(glad)
include_directories(glad/include)
include_directories(glfw)
include_directories(glfw/include)

target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECCT_NAME} glfw)

target_include_directories(${PROJECT_NAME} PUBLIC glad)
target_include_directories(${PROJECT_NAME} PUBLIC glfw)

include_directories(core)
target_link_libraries(${PROJECT_NAME} core)
target_include_directories(${PROJECT_NAME} PUBLIC core)

include_directories(game)
target_link_libraries(${PROJECT_NAME} game)
target_include_directories(${PROJECT_NAME} PUBLIC game)
