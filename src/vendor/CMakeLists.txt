set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm
include_directories("glad")
include_directories("glfw")

add_subdirectory(glad)
add_subdirectory(glfw) # had to sudo apt-get libxinerama-dev

