# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

cmake_minimum_required (VERSION 3.8)

project ("handmade")

# Include sub-projects.
add_subdirectory ("src")

set_property(TARGET "handmade" PROPERTY CXX_STANDARD 17)
add_compile_options("-Wall; -Wextra; -pedantic")

set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm
