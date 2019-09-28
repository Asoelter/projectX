# CMakeList.txt : CMake project for rogue, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})


set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)
#add_subdirectory("util")
add_executable (handmade "main.cpp")

find_package(ALSA REQUIRED) #sudo apt-get install libasound2-dev
if (ALSA_FOUND)
    message("Alsa Found")
    include_directories(${ALSA_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${ALSA_LIBRARIES})
else()
    message("Alsa Not Found")
endif(ALSA_FOUND)

find_package(OpenAL)
if(OpenAL_FOUND)
    message("OPENAL FOUND")
    include_directories(${OPENAL_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${OpenAL_LIBRARIES})
else()
    message("OPENAL NOT FOUND")
endif()

target_link_libraries(handmade ${X11_LIBRARIES})
