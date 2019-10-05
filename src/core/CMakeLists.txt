set(CMAKE_EXPORT_COMPILE_COMMANDS on) #To generate compilation database for ycm


add_library (core shader.h shader.cpp)

include_directories(../)
include_directories(../vendor/glad)
include_directories(../vendor/glad/include)
include_directories(../vendor/glfw)
include_directories(../vendor/glfw/include)

target_link_libraries(core glad)
target_link_libraries(core glfw)

target_include_directories(core PUBLIC ../vendor/glad)
target_include_directories(core PUBLIC ../vendor/glad/include)
target_include_directories(core PUBLIC ../vendor/glfw)