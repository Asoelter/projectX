set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm
project(game)

include_directories(../core)

add_library (game tile_map.h tile_map.cpp)

include_directories(../)
include_directories(../vendor/glad)
include_directories(../vendor/glad/include)
include_directories(../vendor/glfw)
include_directories(../vendor/glfw/include)

target_link_libraries(game glad)
target_link_libraries(game glfw)

set_property(TARGET game PROPERTY CXX_STANDARD 17)
