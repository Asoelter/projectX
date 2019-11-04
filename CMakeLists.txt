# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

cmake_minimum_required (VERSION 3.8)

project ("projectX")

add_definitions(-DHANDMADE_INTERNAL)

# Include sub-projects.
add_subdirectory ("src")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
add_compile_options("-Wall; -Wextra; -pedantic")

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm
