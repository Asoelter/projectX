set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm
project(game)

include_directories(../core)

add_library (game tile_map.h        tile_map.cpp
				  world.h           world.cpp
                  world_position.h  world_position.cpp
                  player.h          player.cpp
                  roamer.h          roamer.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ../core)

include_directories(../)
include_directories(../vendor/glad)
include_directories(../vendor/glad/include)
include_directories(../vendor/glfw)
include_directories(../vendor/glfw/include)

target_link_libraries(game glad)
target_link_libraries(game glfw)

set_property(TARGET game PROPERTY CXX_STANDARD 17)
